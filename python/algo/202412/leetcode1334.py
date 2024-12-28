from functools import cache
from math import inf
from typing import List

# Floyd 全源最短路径 模板
class Solution:
    def findTheCity(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        # 参考题解 - 记忆化搜索
        
        # Begin Floyd 记忆化搜索 模板
        w = [[0 if i == j else inf for j in range(n)] for i in range(n)]
        for u, v, wt in edges:
            w[u][v] = w[v][u] = wt
        
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

    def findTheCity2(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        # 参考题解 - 递推
        
        # Begin Floyd 递推 模板
        w = [[0 if i == j else inf for j in range(n)] for i in range(n)]
        for u, v, wt in edges:
            w[u][v] = w[v][u] = wt
        # k 范围[0,n]
        f = [[[0] * n for _ in range(n)] for _ in range(n+1)]
        f[0] = w

        for k in range(n):
            for i in range(n):
                for j in range(n):
                    f[k+1][i][j] = min(f[k][i][j], f[k][i][k]+f[k][k][j])
        
        # End Floyd 模板
        
        ans, mn_cnt = -1, inf
        for i in range(n):
            cnt = 0
            for j in range(n):
                if i != j and f[n][i][j] <= distanceThreshold:
                    cnt += 1
            if cnt <= mn_cnt:
                ans = i
                mn_cnt = cnt
        
        return ans

    def findTheCity3(self, n: int, edges: List[List[int]], distanceThreshold: int) -> int:
        # 参考题解 - 递推 + 降维
        
        # Begin Floyd 递推 + 降维 模板 
        w = [[0 if i == j else inf for j in range(n)] for i in range(n)]
        for u, v, wt in edges:
            w[u][v] = w[v][u] = wt
        # k 范围[0,n]

        for k in range(n):
            for i in range(n):
                for j in range(n):
                    w[i][j] = min(w[i][j], w[i][k]+w[k][j])
        
        # End Floyd 模板
        
        ans, mn_cnt = -1, inf
        for i in range(n):
            cnt = 0
            for j in range(n):
                if i != j and w[i][j] <= distanceThreshold:
                    cnt += 1
            if cnt <= mn_cnt:
                ans = i
                mn_cnt = cnt
        
        return ans
