from cmath import inf
from collections import defaultdict
import heapq
from typing import List

class Solution:
    def modifiedGraphEdges(self, n: int, edges: List[List[int]], source: int, destination: int, target: int) -> List[List[int]]:
        spec = {}
        graph = defaultdict(list)

        for u, v, w in edges:
            if w == -1:
                spec[(min(u,v),max(u,v))] = 1 # initial is 1
            graph[u].append((v, w))
            graph[v].append((u, w))

        def dijkstra(s:int, graph)->List[int]:
            dist = [inf] * n
            visited = [False] * n

            dist[s] = 0
            # The element in pr is truple (weight, vector)
            pr = []
            heapq.heappush(pr, (s,0))
            while pr:
                _, u = heapq.heappop(pr)
                visited[u] = True
                for e in graph[u]:
                    if not visited[e[0]]:
                        w = spec[(min(u,e[0]),max(u,e[0]))] if e[1]==-1 else e[1]
                        dist[e[0]] = min(dist[e[0]], w+dist[u])
                        heapq.heappush(pr, (dist[e[0]], e[0]))

            return dist


        d0 = dijkstra(source, graph)
        

        if d0[destination] > target:
            return []

        delta = target - d0[destination]

        def dijkstra1(s:int, graph)->List[int]:
            dist = [inf] * n
            visited = [False] * n

            dist[s] = 0
            # The element in pr is truple (weight, vector)
            pr = []
            heapq.heappush(pr, (s,0))
            while pr:
                _, u = heapq.heappop(pr)
                visited[u] = True
                for e in graph[u]:
                    if not visited[e[0]]:
                        w = e[1]
                        if w == -1:
                            w = spec[(min(u,e[0]),max(u,e[0]))] = delta - dist[u] + d0[e[0]]
                        dist[e[0]] = min(dist[e[0]], w+dist[u])
                        heapq.heappush(pr, (dist[e[0]], e[0]))

            return dist
        
        d1 = dijkstra1(source, graph)
        print(d1)
        if d1[destination] != target:
            return []

        ans = []
        for key, w in spec.items():
            ans.append([key[0],key[1],w])
        
        for u, v, w in edges:
            if w != -1:
                ans.append([u,v,w])

        return ans

if __name__ == "__main__":
    sol = Solution()
    n, edges, source, destination, target = 5, [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], 0, 1, 5
    n, edges, source, destination, target = 4, [[0,1,-1],[1,2,-1],[3,1,-1],[3,0,2],[0,2,5]], 2, 3, 8
    print(sol.modifiedGraphEdges(n, edges, source, destination, target))