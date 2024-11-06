from math import isqrt
from typing import List

# 埃氏筛 求 质数
MX = 10 ** 5 + 1
is_prime = [True] * MX
is_prime[1] = False
for i in range(2, isqrt(MX) + 1):
    if is_prime[i]:
        for j in range(i * i, MX, i):
            is_prime[j] = False

# 周赛 364
class Solution:
    def countPaths(self, n: int, edges: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        # 求以质数为根的子树的节点，(不包含编号为质数的节点)
        nodes = []
        def dfs(u:int, fa:int) :
            nodes.append(u)
            for v in g[u]:
                if v == fa: continue
                if not is_prime[v]: dfs(v, u)
        
        count = [-1] * n
        for x in range(1, n+1):
            if not is_prime: continue # 非质数，忽略
            


