from functools import cache
from typing import List

# 动态规划 - 网格图 DP - 2.2 进阶
class Solution:
    def uniquePaths(self, grid: List[List[int]]) -> int:
        # 自行解答，动态规划还是用记忆化搜索容易实现
        mod = 10 ** 9 + 7
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(i: int, j: int, d: int) -> int :
            # d. -1:initial, 0: up, 1: left
            if i >= m or j >= n: return 0
            if i == m-1 and j == n - 1:
                return 1

            if grid[i][j] == 0:
                return dfs(i+1, j, 0) + dfs(i, j+1, 1)
            elif grid[i][j] == 1:
                if d == 0: return dfs(i, j+1, 1)
                else: return dfs(i+1, j, 0)
        ans = dfs(0, 0, -1)
        return ans % mod