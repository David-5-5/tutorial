from typing import List

# 一、网格图 DFS
class Solution:
    def numIslands(self, grid: List[List[str]]) -> int:
        m, n = len(grid), len(grid[0])
        vis = [[False] * n for _ in range(m)]

        def dfs(x: int, y: int) -> None:
            if x < 0 or x >= m or y < 0 or y >= n or vis[x][y] or grid[x][y] == '0': return
            vis[x][y] = True
            dfs(x+1, y)
            dfs(x-1, y)
            dfs(x, y+1)
            dfs(x, y-1)
        
        ans = 0
        for x in range(m):
            for y in range(n):
                if not vis[x][y] and grid[x][y] == '1':
                    ans += 1
                    dfs(x, y)
        return ans        