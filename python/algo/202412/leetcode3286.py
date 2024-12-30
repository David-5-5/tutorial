from cmath import inf
import heapq
from typing import List

# 双周赛 139 Dijkstra 最短距离
class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
        # 自行解答
        m, n = len(grid), len(grid[0])

        pq = [(0, 0)]
        vis = [False] * (m*n)
        dis = [inf] * (m*n)
        dis[0] = grid[0][0]

        while pq:
            _, u = heapq.heappop(pq)
            if vis[u]: continue

            vis[u] = True
            x, y = u // n, u % n
            for r, c in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                if 0<=r<m and 0<=c<n:
                    v = r * n + c
                    if not vis[v] and dis[v] > dis[u]+grid[r][c]:
                        dis[v] = dis[u]+grid[r][c]
                        heapq.heappush(pq, (dis[v], v))

        return dis[m*n-1] < health

    def findSafeWalk2(self, grid: List[List[int]], health: int) -> bool:
        # 自行解答，vis, dis 使用二位数组
        m, n = len(grid), len(grid[0])

        pq = [[0, (0,0)]]
        vis = [[False] * n for _ in range(m)]
        dis = [[inf] * n for _ in range(m)]
        dis[0][0] = grid[0][0]

        while pq:
            _, (x,y) = heapq.heappop(pq)
            if vis[x][y]: continue

            vis[x][y] = True
            for r, c in [(x+1,y),(x-1,y),(x,y+1),(x,y-1)]:
                if 0<=r<m and 0<=c<n:
                    if not vis[r][c] and dis[r][c]  > dis[x][y]+grid[r][c]:
                        dis[r][c] = dis[x][y]+grid[r][c]
                        heapq.heappush(pq, (dis[r][c], (r,c)))

        return dis[m-1][n-1] < health