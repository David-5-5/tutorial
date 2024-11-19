from functools import cache
from typing import List

MAX_HALF = 13
# 周赛 369
class Solution:
    def maximumPoints(self, edges: List[List[int]], coins: List[int], k: int) -> int:
        # 自行解答，树上 DP
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        @cache
        def dfs(u:int, fa:int, half:int) -> int:
            # 使用方式二
            res1 = coins[u] // pow(2, half) - k
            res2 = coins[u] // pow(2, half) // 2
            for v in g[u]:
                if v == fa:continue
                res1 += dfs(v, u, min(MAX_HALF,half))
                res2 += dfs(v, u, min(MAX_HALF,half+1))
            return max(res1, res2)

        return dfs(0, -1, 0)        

if __name__ == "__main__":
    sol = Solution()
    edges, coins, k = [[0,1],[1,2],[2,3]], [10,10,3,3], 5
    print(sol.maximumPoints(edges, coins, k))