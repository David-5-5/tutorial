from functools import cache
from math import inf
from typing import List

# Floyd 全源最短路径 模板
class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        # 参考题解 - 记忆化搜索
        
        # Begin Floyd 模板
        # g = [[] for _ in range(n)]
        w = [[0 if i == j else inf for j in range(n)] for i in range(n)]
        for u, v, weight in edges:
            # g[u].append(v)
            # g[v].append(u)
            w[u][v] = weight
            w[v][u] = weight
        
        @cache
        def dfs(k:int, i:int, j:int) -> int:
            if k < 0: return w[i][j]
            return min(dfs(k-1, i, j), dfs(k-1,i,k)+dfs(k-1,k,j))
        
        # End Floyd 模板
        
        ans, mn_cnt = -1, inf
        for i in range(n):
            cnt = 0
            for j in range(n):
                if i != j and dfs(n-1, i, j) <= distanceThreshold:
                    cnt += 1
            if cnt <= mn_cnt:
                ans = i
                mn_cnt = cnt
        
        return ans

