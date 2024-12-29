from cmath import inf
import heapq
from typing import List

# 双周赛 139 Dijkstra 最短距离
class Solution:
    def findSafeWalk(self, grid: List[List[int]], health: int) -> bool:
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
        print(dis)
        return dis[m*n-1] < health