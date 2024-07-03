from collections import defaultdict
from math import inf
from typing import List
import heapq
# graph is a dict ,which key is the vertex(from 0,..,n-1) and 
# value is list of ajacent vertex and it weigth
class shortest:
    def dijkstra(self, n:int, start :int, graph :List[List[int]])->List[int]:
        dist = [inf] * n
        visited = [False] * n

        dist[start] = 0
        # The element in pr is truple (weight, vertex)
        pr = []
        heapq.heappush(pr, (0,start)) 
        while pr:
            _, u = heapq.heappop(pr)
            if visited[u]:
                continue
            visited[u] = True
            for v, w in graph[u]:
                if not visited[v] and dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    heapq.heappush(pr, (dist[v], v))

        return dist
        

if __name__ == "__main__":
    graph = {}
    graph[0] = [[1,1],[2,12]]
    graph[1] = [[0,1],[2,9],[3,3]]
    graph[2] = [[0,12],[1,9],[3,4],[4,5]]
    graph[3] = [[1,3],[2,4],[4,13],[5,15]]
    graph[4] = [[2,5],[3,13],[5,4]]
    graph[5] = [[3,15],[4,4]]
    short = shortest()
    print(short.dijkstra(6, 0, graph))


