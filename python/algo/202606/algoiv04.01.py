from typing import List


class Solution:
    def findWhetherExistsPath(self, n: int, graph: List[List[int]], start: int, target: int) -> bool:
        g = [[] for _ in range(n)]
        for e in graph:
            g[e[0]].append(e[1])
        
        visited = [False] * n
        def dfs(u: int) -> bool:
            if u == target: return True

            for v in g[u]:
                if not visited[v]:
                    visited[v] = True
                    if dfs(v): return True
            
            return False

        return dfs(start)