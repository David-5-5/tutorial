from cmath import inf
import heapq
from typing import List

# 双周赛 128
class Solution:
    def minimumTime(self, n: int, edges: List[List[int]], disappear: List[int]) -> List[int]:
        # 自行解答，使用 Dijkstra 最短距离，当 dis[i] >= disappear[i] dis[i] = inf
        g = [[] for _ in range(n)]
        edge_d = {}
        for u, v, l in edges:
            if (min(u,v),max(u,v)) not in edge_d.keys() or (min(u,v),max(u,v)) in edge_d.keys() and l < edge_d[(min(u,v),max(u,v))]:
                edge_d[(min(u,v),max(u,v))] = l

        for (u, v), l in edge_d.items():
            g[u].append((v, l))
            g[v].append((u, l))

        pq = [(0, 0)]
        vis = [False] * n
        dis = [inf] * n
        dis[0] = 0

        while pq:
            _, u = heapq.heappop(pq)
            if vis[u]: continue

            vis[u] = True
            if dis[u] >= disappear[u]:
                dis[u] = inf
                continue
            for v, c in g[u]:
                if not vis[v] and dis[v] > dis[u]+c:
                    dis[v] = dis[u]+c
                    heapq.heappush(pq, (dis[v], v))

        return [-1 if x == inf else x for x in dis]

if __name__ == "__main__":
    sol = Solution()
    n, edges, disappear = 3, [[0,1,2],[1,2,1],[0,2,4]], [1,1,5]
    print(sol.minimumTime(n, edges, disappear))