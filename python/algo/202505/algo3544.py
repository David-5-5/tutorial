from functools import cache
from typing import List

# 动态规划 - 12.2 树上最大独立集
class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        # 自行解答
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        # 内存超出限制,因此dfs递归函数避免使用 fa 参数,预计算每个节点的父节点
        fa  = [-1] * n
        q = [0]
        while q:
            tmp = q
            q = []
            for u in tmp:
                for v in g[u]:
                    if v != 0 and fa[v] == -1:
                        fa[v] = u
                        q.append(v)

        @cache
        def dfs(u: int, d:int, rev:bool) -> int:
            # non reverse
            res = -nums[u] if rev else nums[u]
            for v in g[u]:
                if v == fa[u]: continue
                res += dfs(v, max(d-1, 0), rev)

            if d == 0: # reverse
                rev = not rev
                res1 = -nums[u] if rev else nums[u]
                for v in g[u]:
                    if v == fa[u]: continue
                    res1 += dfs(v, k-1, rev)
                if res1 > res: res = res1
            return res

        return dfs(0, 0, False)
    
    def subtreeInversionSum2(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        # 参考题解 手写cache,避免内存溢出
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        cache = {}
        
        def dfs(u: int, fa:int, d:int, rev:int) -> int:
            # non reverse
            t = u << 8 | d << 1 | rev
            if t in cache: return cache[t]

            res = -nums[u] if rev else nums[u]
            for v in g[u]:
                if v == fa: continue
                res += dfs(v, u, max(d-1, 0), rev)

            if d == 0: # reverse
                rev ^= 1
                res1 = -nums[u] if rev else nums[u]
                for v in g[u]:
                    if v == fa: continue
                    res1 += dfs(v, u, k-1, rev)
                if res1 > res: res = res1
            
            cache[t] = res
            return res

        return dfs(0, -1, 0, False)