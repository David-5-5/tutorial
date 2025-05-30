from functools import cache
import heapq
from math import inf
from typing import List

# 动态规划 - 13. 图 DP
class Solution:
    def countRestrictedPaths(self, n: int, edges: List[List[int]]) -> int:
        # 自行解答 Dijkstra + 记忆化搜索
        g = [[] for _ in range(n)]
        
        for u, v, w in edges:
            u, v = u-1, v-1
            g[u].append((v, w))
            g[v].append((u, w))

        dist = [inf] * n
        start = n-1
        
        dist[start] = 0
        # The element in pr is truple (weight, vertex)
        pr = []
        heapq.heappush(pr, (0,start)) 
        while pr:
            _, u = heapq.heappop(pr)

            for v, w in g[u]:
                if dist[v] > dist[u] + w:
                    dist[v] = dist[u] + w
                    heapq.heappush(pr, (dist[v], v))

        mod = 10 ** 9 + 7
        @cache
        def dfs(u:int) -> int :
            if u == n-1: return 1

            res = 0
            for v, _ in g[u]:
                if dist[v] < dist[u]:
                    res = (res + dfs(v)) % mod
            return res
        return dfs(0)