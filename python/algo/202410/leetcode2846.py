from typing import List

# 周赛 361
class Solution:
    def minOperationsQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        g = [[] for _ in range(n)]

        for u, v, w in edges:
            g[u].append((v, w))
            g[v].append((u, w))
        
        