class Solution:
    def uniquePathsIII(self, grid) -> int:
        m = len(grid)
        n = len(grid[0])

        begin, end = (0,0), (0,0)
        visited = []
        count_of_v = 2
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    begin = (r, c)
                elif grid[r][c] == 2:
                    end = (r, c)
                elif grid[r][c] == 0:
                    count_of_v += 1
        
        def dfs(point):
            visited.append(point)
            if point == (end) and len(visited) == count_of_v:
                return 1
            elif point == (end):
                return 0
        
            count = 0
            for x, y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                n_x, n_y = x + point[0], y + point[1]
                if 0 <= n_x < m and 0 <= n_y < n and (n_x, n_y) not in visited and grid[n_x][n_y] in (0, 2):
                    count += dfs((n_x, n_y))
                    # 回溯
                    inx = visited.index((n_x, n_y))
                    visited.pop(inx)

            return count

        return dfs(begin)

if __name__ == "__main__":
    sol = Solution()
    grid = [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
    # grid = [[0,1],[2,0]]
    print(sol.uniquePathsIII(grid))