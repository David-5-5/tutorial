from functools import cache
from typing import List


class Solution:
    def maxMoves(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(r:int, c:int) -> int:
            if c == n-1:return 0

            res = 0
            for nr, nc in (r-1, c+1), (r,c+1), (r+1,c+1):
                if 0<=nr<m and 0<=nc<n and grid[r][c] < grid[nr][nc]:
                    res = max(res, 1+dfs(nr, nc))

            return res

        return max(dfs(r, 0) for r in range(m))

if __name__ == "__main__":
    sol = Solution()
    grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
    print(sol.maxMoves(grid))