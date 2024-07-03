from typing import List


class Solution:
    def onesMinusZeros(self, grid: List[List[int]]) -> List[List[int]]:
        m, n = len(grid), len(grid[0])
        r = [0] * m
        c = [0] * n
        for i in range(m):
            for j in range(n):
                r[i] += grid[i][j]
                c[j] += grid[i][j]
        
        diff = [[0] * n for _ in range(m)]
        for i in range(m):
            for j in range(n):
                diff[i][j] = 2 * r[i] + 2* c[j]  - m - n

        return diff
