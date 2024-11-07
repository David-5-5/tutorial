from typing import List

# 周赛 365
class Solution:
    def countVisitedNodes(self, edges: List[int]) -> List[int]:
        n = len(edges)
        g = [[] for _ in range(n)]
        deg = [0] * n

        for u, v in enumerate(edges):
            g[u].append[v]
            deg[v] += 1
