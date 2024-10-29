from collections import defaultdict
from typing import List

# 双周赛 131
class Solution:
    def queryResults(self, limit: int, queries: List[List[int]]) -> List[int]:
        cnt = defaultdict(int)
        color = {}
        ans = []
        for x, y in queries:
            if x in color:
                c = color[x]
                cnt[c] -= 1
                if cnt[c] == 0: del cnt[c]
            color[x] = y
            cnt[y] += 1
            ans.append(len(cnt))
        return ans

if __name__ == "__main__":
    sol = Solution() 
    limit, queries = 4, [[1,4],[2,5],[1,3],[3,4]]
    print(sol.queryResults(limit, queries))