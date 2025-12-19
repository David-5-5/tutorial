from typing import List

# 三、网格图 0-1 BFS
class Solution:
    def minMoves(self, matrix: List[str]) -> int:
        dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        # 自行解答
        m, n = len(matrix), len(matrix[0])
        if matrix[m-1][n-1] == '#': return -1
        door_coor = [[] for _ in range(26)]
        for i, row in enumerate(matrix):
            for j, ch in enumerate(row):
                if ord(ch) >= ord('A') and ord(ch) <= ord('Z'):
                    door_coor[ord(ch)-ord('A')].append((i, j))

        q = []
        vis = [[False] * n for _ in range(m)]
        if matrix[0][0] == '.':
            q.append((0, 0))
            vis[0][0] = True
        else:
            for i, j in door_coor[ord(matrix[0][0])-ord('A')]:
                q.append((i, j))
                vis[i][j] = True
        
        step = 0
        while q:
            tmp = q
            q = []
            for x, y in tmp:
                
                if x == m-1 and y == n-1: return step
                for d in dirs:
                    dx, dy = x + d[0], y + d[1]
                    if dx < 0 or dx >= m or dy < 0 or dy >= n or matrix[dx][dy] == '#' or vis[dx][dy]: continue
                    if matrix[dx][dy] == '.':
                        q.append((dx, dy))
                        vis[dx][dy] = True
                    else:
                        for i, j in door_coor[ord(matrix[dx][dy])-ord('A')]:
                            q.append((i, j))
                            vis[i][j] = True
            step += 1
        return -1