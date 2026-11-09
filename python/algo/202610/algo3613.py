from typing import List


class Solution:

    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        # 自行解答，二分，性能差
        mx_w = max([w for _, _, w in edges])

        def check(limit: int) -> bool:
            g = [[] for _ in range(n)]
            for u, v, w in edges:
                if w <= limit:
                    g[u].append(v)
                    g[v].append(u)
            
            vis = [False] * n
            def dfs(u: int) :
                for v in g[u]:
                    if not vis[v]:
                        vis[v] = True
                        dfs(v)
            cc = 0
            for i in range(n):
                if not vis[i]:
                    cc += 1
                    vis[i] = True
                    dfs(i)
            return cc <= k
        
        l, r = -1, mx_w + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid):
                r = mid
            else: l = mid
        return r
