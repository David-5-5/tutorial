from typing import List


class Solution:
    def minFlips(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        row_p = col_p = 0
        for i in range(m):
            for j in range(n//2):
                if grid[i][j] != grid[i][n-j-1]:
                    row_p += 1

        for j in range(n):
            for i in range(m//2):
                if grid[i][j] != grid[m-1-i][j]:
                    col_p += 1


        return min(row_p, col_p)
