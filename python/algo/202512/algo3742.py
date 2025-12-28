from cmath import inf
from functools import cache
from typing import List

# 动态规划 - 网格图 DP - 2.1 基础
class Solution:
    def maxPathScore(self, grid: List[List[int]], k: int) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(i: int, j: int, c: int) -> int:
            if c<0 or i < 0 or j < 0: return -inf
            if i == 0 and j == 0: return grid[0][0]

            return grid[i][j] + max(dfs(i-1, j, c-(1 if grid[i][j] else 0)), dfs(i, j-1, c-(1 if grid[i][j] else 0)))

        ans = dfs(m-1, n-1, k)
        return ans if ans >= 0 else -1
