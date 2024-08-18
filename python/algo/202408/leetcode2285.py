from typing import List

# 双周赛 79 
class Solution:
    def maximumImportance(self, n: int, roads: List[List[int]]) -> int:
        # 自行解答
        g = [[] for _ in range(n)]

        for u, v in roads:
            g[u].append(v)
            g[v].append(u)

        dg = [len(u) for u in g ]
        dg.sort()

        ans = 0
        for d, m in zip(dg, [i + 1 for i in range(n)]):
            ans += d * m
        
        return ans
        
    def maximumImportance2(self, n: int, roads: List[List[int]]) -> int:
        # 参考题解, 代码更简洁紧凑
        g = [0] * n

        for u, v in roads:
            g[u] += 1
            g[v] += 1

        g.sort()

        return sum([d * i for d, i in enumerate(g, 1)])
        