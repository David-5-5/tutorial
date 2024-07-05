# 模板题，使用 Dijkstra/Folyd 算法 
from collections import defaultdict
import heapq
from typing import List


class Graph:
    # Dijkstra algorithm
    def __init__(self, n: int, edges: List[List[int]]):
        g = defaultdict(list)
        for u, v, w in edges:
            g[u].append((v, w))
        self.g = g
        self.n = n

    def addEdge(self, edge: List[int]) -> None:
        self.g[edge[0]].append((edge[1], edge[2]))

    
    def shortestPath(self, node1: int, node2: int) -> int:

        dist = [float('inf')] * self.n
        dist[node1] = 0
        pq = [(0, node1)]
        while pq:
            d, u = heapq.heappop(pq)
            if d > dist[u]:
                continue
            for v, w in self.g[u]:
                if d + w < dist[v]:
                    dist[v] = d + w
                    heapq.heappush(pq, (dist[v], v))
        return -1 if dist[node2] == float('inf') else dist[node2]

class Graph2:
    # Folyd algorithm
    def __init__(self, n: int, edges: List[List[int]]):
        self.n = n
        self.dp = [[0 if i==j else float("inf") for i in range(self.n)] for j in range(self.n)]

        g = self.dp
        for u, v, w in edges:
            g[u][v] = w
        for k in range(self.n):
            for i in range(self.n):
                for j in range(self.n):
                    # g[i][j] = min(g[i][j], g[i][k] + g[k][j])
                    if g[i][k] + g[k][j] < g[i][j]:
                        g[i][j] = g[i][k] + g[k][j]
    
    def addEdge(self, edge: List[int]) -> None:
        u, v, w = edge
        g = self.dp
        if g[u][v] < w:
            return
        g[u][v] = w
        for i in range(self.n):
            for j in range(self.n):
                # g[i][j] = min(g[i][j], g[i][u] + g[u][v] + g[v][j]) 
                if g[i][u] + g[u][v] + g[v][j] < g[i][j]:
                    g[i][j] = g[i][u] + g[u][v] + g[v][j]

    def shortestPath(self, node1: int, node2: int) -> int:
        dp = self.dp
        return -1 if dp[node1][node2] == float('inf') else dp[node1][node2]

# Your Graph object will be instantiated and called as such:
# obj = Graph(n, edges)
# obj.addEdge(edge)
# param_2 = obj.shortestPath(node1,node2)