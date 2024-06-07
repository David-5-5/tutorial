from typing import Dict,List
import heapq
# graph is a dict ,which key is the vector(from 0,..,n-1) and 
# value is list of ajacent vector and it weigth
class shortest:
    def dijkstra(self, graph)->List[int]:
        n = len(graph)
        dist = [float("inf")] * n
        visited = [False] * n

        dist[0] = 0
        # The element in pr is truple (weight, vector)
        pr = []
        heapq.heappush(pr, (0,0)) 
        while pr:
            _, u = heapq.heappop(pr)
            visited[u] = True
            for e in graph[u]:
                if not visited[e[0]]:
                    dist[e[0]] = min(dist[e[0]], e[1]+dist[u])
                    heapq.heappush(pr, (dist[e[0]], e[0]))

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
    print(short.dijkstra(graph))
