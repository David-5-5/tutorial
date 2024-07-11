from collections import deque
from typing import List

# week 338， refer to https://leetcode.cn/problems/collect-coins-in-a-tree/solutions/2191371/tuo-bu-pai-xu-ji-lu-ru-dui-shi-jian-pyth-6uli/
# Topological sorting, 拓扑排序
class Solution:
    def collectTheCoins(self, coins: List[int], edges: List[List[int]]) -> int:
        n = len(coins)
        g = [[] for _ in range(n)]
        d = [0] * n # degree, undirected graphs, the degree of leaf is 1 nor 0
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
            d[u] += 1
            d[v] += 1
        # d = list(map(len,g))

        left_edges = n - 1
        # First topology sort to get rid of leaf without coins
        q = [] # queue of node degree is 1
        for i in range(n):
            if coins[i] == 0 and d[i] == 1:
                q.append(i)
        
        while q:
            left_edges -= 1
            for v in g[q.pop()]:
                d[v] -= 1
                if d[v] == 1 and coins[v] == 0:
                    q.append(v)
        
        # Second topology sort to get rid of leaf with coins
        for i in range(n):
            if coins[i] == 1 and d[i] == 1:
                q.append(i)
        left_edges -= len(q)

        # Third, get rid of the rest node with degree is 1
        for u in q:
            for v in g[u]:
                d[v] -= 1
                if d[v] == 1: left_edges -= 1
        
        return max(left_edges*2, 0)

if __name__ == "__main__":
    sol = Solution()
    coins, edges = [1,0,0,0,0,1], [[0,1],[1,2],[2,3],[3,4],[4,5]]
    coins, edges = [0,0,0,1,1,0,0,1],[[0,1],[0,2],[1,3],[1,4],[2,5],[5,6],[5,7]]
    print(sol.collectTheCoins(coins, edges))