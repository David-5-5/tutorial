from cmath import inf
from collections import defaultdict
import heapq
from typing import List

class Solution:
    # pass the testcase with 416ms
    # prevois version pass with 6387ms
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
            heapq.heappush(pr, (0, s))
            while pr:
                _, u = heapq.heappop(pr)
                if visited[u]:
                    continue                
                visited[u] = True
                for v, w in graph[u]:
                    if not visited[v] and dist[v] > (spec[(min(u,v),max(u,v))] if w==-1 else w) + dist[u]:
                        dist[v] = (spec[(min(u,v),max(u,v))] if w==-1 else w) + dist[u]
                        heapq.heappush(pr, (dist[v], v))
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
            heapq.heappush(pr, (0, s))
            while pr:
                _, u = heapq.heappop(pr)
                if visited[u]:
                    continue                
                visited[u] = True
                for v, w in graph[u]:
                    if visited[v]:
                        continue
                    if w == -1:
                        spec[(min(u,v),max(u,v))] = max(delta - dist[u] + d0[v],1)
                    if dist[v] > (spec[(min(u,v),max(u,v))] if w==-1 else w) + dist[u]:

                        dist[v] = (spec[(min(u,v),max(u,v))] if w==-1 else w) + dist[u]
                        heapq.heappush(pr, (dist[v], v))

            return dist
        
        d1 = dijkstra1(source, graph)

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
    print(sol.modifiedGraphEdges(n, edges, source, destination, target))