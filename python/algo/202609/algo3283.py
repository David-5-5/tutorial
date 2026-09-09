from cmath import inf
from functools import cache
from typing import List


class Solution:
    def maxMoves(self, kx: int, ky: int, positions: List[List[int]]) -> int:
        DIRS = [[2, 1], [2, -1], [-2, 1], [-2, -1], [1, 2], [1, -2], [-1, 2], [-1, -2]]
        positions.append([kx, ky])  # 把起点放在最后，递归从 -1 开始
        n = len(positions)          # state 位数为 n-1 == len(positions) 原始
 
        def calc(sx: int, sy: int, ex:int, ey: int) :
            dist = 0
            vis = set()
            q = [(sx, sy)]
            vis.add((sx, sy))
            while q:
                nxt = []
                for x, y in q:
                    
                    if x == ex and y == ey: return dist

                    for _x, _y in DIRS:
                        nx, ny = x+_x, y+_y
                        if 0<=nx<50 and 0<=ny<50 and (nx, ny) not in vis:
                            nxt.append((nx, ny))
                            vis.add((nx, ny))
                dist += 1
                q = nxt
        
        p2p = [[-1] * n for _ in range(n)]
        
        for i in range(n):
            for j in range(i+1, n):
                p2p[i][j] = p2p[j][i] = calc(positions[i][0], positions[i][1], positions[j][0], positions[j][1])

        @cache
        def dfs(i: int, state: int) -> int:
            cnt = state.bit_count()
            if cnt == n-1: return 0

            if cnt % 2: # 
                res = inf
                for j in range(n-1):
                    if (state >> j) & 1 == 0:
                        res = min(res, p2p[j][i] + dfs(j, state|1<<j))
                return res
            else:
                res = 0
                for j in range(n-1):
                    if (state >> j) & 1 == 0:
                        res = max(res, p2p[j][i] + dfs(j, state|1<<j))
                return res

        return dfs(-1, 0)
                