from collections import defaultdict
from typing import List

# 周赛 332
class Solution:
    def substringXorQueries(self, s: str, queries: List[List[int]]) -> List[List[int]]:
        # 自行解答 
        l, n, qn = 0, len(s), len(queries)
        ans = [[-1,-1] for _ in range(qn)]
        
        val_d  = defaultdict(list)
        for i, (fir, sec) in enumerate(queries):
            val_d[fir^sec].append(i)
        
        while l < n:
            if s[l] == '1':
                for r in range(1, 31):
                    x = int(s[l:l+r], 2)
                    if val_d[x]:
                        for inx in val_d[x]:
                            ans[inx] = [l, l+r-1]
                    del val_d[x]
            else:
                if val_d[0]:
                    for inx in val_d[0]:
                        ans[inx] = [l, l]
                del val_d[0]
            l += 1
        return ans

    def substringXorQueries2(self, s: str, queries: List[List[int]]) -> List[List[int]]:
        ans = []
        pos = defaultdict(list)
        for i in range(len(s)):
            if s[i] == '0':
                if 0 not in pos:
                    pos[0] = [i, i]
                continue
            for l in range(30):
                val = int(s[i:i+l+1], base=2)
                if val not in pos:
                    pos[val] = [i, i+l]

        for q in queries:
            val = q[0] ^ q[1]
            if val in pos:
                ans.append(pos[val])
            else: ans.append([-1, -1])

        return ans
if __name__ == "__main__":
    sol = Solution()
    s, queries = "101101", [[0,5],[1,2]]
    s, queries = "111010110", [[4,2],[3,3],[6,4],[9,9],[10,28],[0,470],[5,83],[10,28],[8,15],[6,464],[0,3],[5,8],[7,7],[8,8],[6,208],[9,15],[2,2],[9,95]]
    print(sol.substringXorQueries(s, queries))