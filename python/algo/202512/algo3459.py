from functools import cache
from typing import List

# 动态规划 - 网格图 DP - 2.2 进阶
class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        dirs = [(-1, -1), (-1, 1), (1, 1), (1, -1)]
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(x: int, y:int, d: int, prev: int, t: bool) -> int:
            res = 0
            if d == -1:
                for nd, [dx, dy] in enumerate(dirs):
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] == 2:
                        res = max(res, dfs(nx, ny, nd, 2, False))
            else:
                nx, ny = x + dirs[d][0], y + dirs[d][1]
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] + prev == 2:
                    res = max(res, dfs(nx, ny, d, 2 - prev, t))
                if not t:
                    nd = (d + 1) % 4    # 向右
                    nx, ny = x + dirs[nd][0], y + dirs[nd][1]
                    if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] + prev == 2:
                        res = max(res, dfs(nx, ny, nd, 2 - prev, True))

            return res + 1

        ans = 0
        for r, row in enumerate(grid):
            for c, v in enumerate(row):
                if v == 1: ans = max(ans, dfs(r, c, -1, 0, False))
            
        return ans   