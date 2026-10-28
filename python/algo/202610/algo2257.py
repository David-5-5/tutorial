from typing import List


DIRS = (0, -1), (0, 1), (-1, 0), (1, 0)
class Solution:
    def countUnguarded(self, m: int, n: int, guards: List[List[int]], walls: List[List[int]]) -> int:
        grid = [[0] * n for _ in range(m)]

        for u, v in guards: grid[u][v] = - 1
        for u, v in walls: grid[u][v] = - 1
        
        for d in DIRS:
            for u, v in guards:
                r, c = u + d[0], v + d[1]
                while 0 <= r < m and 0 <= c < n and grid[r][c] != -1:
                    grid[r][c] = 1
                    r += d[0]
                    c += d[1]
        
        return sum([c==0 for row in grid for c in row])
