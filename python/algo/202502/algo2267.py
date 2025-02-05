from functools import cache
from typing import List

# 动态规划 - 网格图 DP - 进阶
class Solution:
    def hasValidPath(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])

        if grid[0][0] == ')' or grid[m-1][n-1] == '(': return False

        @cache
        def dfs(i:int, j:int, k:int) -> bool:
            if i >= m or j >=n or k>(m+n-1) // 2 or k < 0: return False
            if i == m-1 and j == n-1:
                if k == 1: return True
                else: return False
            
            if dfs(i+1, j, k + (1 if grid[i][j]=='(' else -1)): return True
            if dfs(i, j+1, k + (1 if grid[i][j]=='(' else -1)): return True
            return False
        
        return dfs(0,0,0)