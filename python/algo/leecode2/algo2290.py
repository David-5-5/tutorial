from typing import List
from collections import deque
class Solution:
    def minimumObstacles(self, grid: List[List[int]]) -> int:
        r, c = len(grid), len(grid[0])
        path = [float("inf")] * (r*c)

        path[0] = grid[0][0]

        tovis = deque()
        tovis.append((0,0))
        while tovis:
            x, y = tovis.popleft()
            for _x, _y in [(0,1),(0,-1),(-1,0),(1,0)]:
                if 0<=x+_x<r and 0<=y+_y<c:
                    inx = (x+_x)*c + y+_y
                    if path[inx] > path[x*c+y] + grid[x+_x][y+_y]:
                        path[inx] = path[x*c+y] + grid[x+_x][y+_y]
                        if grid[x+_x][y+_y] == 0:
                            tovis.appendleft((x+_x, y+_y))
                        else:
                            tovis.append((x+_x, y+_y))

        return path[-1]
    
if __name__ == "__main__":
    sol = Solution()
    grid = [[0,1,1],[1,1,0],[1,1,0]]
    print(sol.minimumObstacles(grid))