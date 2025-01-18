from math import inf
from typing import List


class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        # dfs
        n = len(nums)
        mx_len = 0
        mn_cnt = inf

        vets = set()

        
        g = [[] for _ in range(n)]
        for u, v, l in edges:
            g[u].append((v, l))
            g[v].append((u, l))


        def dfs(u:int, fa:int) -> tuple[int, int]:
            vets.add(nums[u])
            res = 0
            cnt = inf
            for v, l in g[u]:
                if v == fa: continue
                if nums[v] not in vets:
                    r, c = dfs(v, u)
                    if l + r > res:
                        res = l + r
                        cnt = 1 + c
                    elif l+r == res:
                        cnt = min(cnt, 1+c)
                    vets.remove(nums[v])
                else:que.append((v, u)) # 重新遍历
            
            if cnt == inf:cnt = 1
            return res, cnt

        que = [(0,-1)]
        while que:
            u, fa = que.pop(0)
            r, c = dfs(u, fa)
            vets.clear()
            if r > mx_len:
                mx_len = r
                mn_cnt = c
            elif r == mx_len: mn_cnt = min(mn_cnt, c)

        return [mx_len, mn_cnt]
        
if __name__ == "__main__":
    sol = Solution()
    edges = [[1,0,2],[0,2,10]]
    nums = [2,4,4]
    print(sol.longestSpecialPath(edges, nums))