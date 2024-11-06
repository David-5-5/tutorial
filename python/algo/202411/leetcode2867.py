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
        g = [[] for _ in range(n+1)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        # 求以质数为根的子树的节点，(不包含编号为质数的节点)
        nodes = []
        def dfs(u:int, fa:int) :
            nodes.append(u)
            for v in g[u]:
                if v != fa and not is_prime[v]: dfs(v, u)
        
        count = [-1] * (n+1)
        ans = 0
        for x in range(1, n+1):
            if not is_prime[x]: continue # 非质数，忽略

            left = 0
            for y in g[x]:
                if is_prime[y]: continue  # 非质数，忽略
                if count[y] == -1:
                    nodes.clear()
                    dfs(y, -1)
                    for v in nodes:
                        count[v] = len(nodes)
                ans += left * count[y]
                left += count[y]
            ans += left
        return ans

if __name__ == "__main__":
    sol = Solution()
    n, edges = 5, [[1,2],[1,3],[2,4],[2,5]]
    print(sol.countPaths(n, edges))
                    

