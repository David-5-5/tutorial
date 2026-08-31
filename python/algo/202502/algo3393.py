from functools import cache
from typing import List

# 动态规划 - 网格图 DP - 基础
class Solution:
    def countPathsWithXorValue(self, grid: List[List[int]], k: int) -> int:
        mod = 10 ** 9 + 7
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(i: int, j:int, p:int):
            if i >= m or j >= n: return 0
            if i == m-1 and j == n-1:
                if p ^ grid[i][j] == k: return 1
                else: return 0
            
            res = dfs(i+1,j,p^grid[i][j])
            res += dfs(i,j+1,p^grid[i][j])
            return res % mod
        return dfs(0,0,0)
    
