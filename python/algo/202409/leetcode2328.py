from typing import List

# 周赛 300
class Solution:
    def countPaths(self, grid: List[List[int]]) -> int:
        MOD = 10 ** 9 + 7
        m , n = len(grid), len(grid[0])
        visited = [[-1] * n for _ in range(m)]

        def dfs(x:int, y:int):
            if visited[x][y] != -1: return visited[x][y]

            visited[x][y] = 1
            for u, v in [(0,1),(0,-1),(-1,0),(1,0)]:
                if 0 <= x + u < m and 0 <= y + v < n and grid[x][y] < grid[x+u][y+v]:
                    visited[x][y] += dfs(x+u,y+v)
            visited[x][y] = visited[x][y] % MOD
            return visited[x][y]

        ans = 0
        for i in range(m):
            for j in range(n):
                ans += dfs(i,j)
        return ans % MOD


if __name__ == "__main__":
    sol = Solution()
    grid = [[1,1],[3,4]]
    print(sol.countPaths(grid))
