from typing import List

# 复习
# 动态规划 - 12.1 树的直径
class Solution:
    def minimumDiameterAfterMerge(self, edges1: List[List[int]], edges2: List[List[int]]) -> int:
        def diameter(edges: List[List[int]]) -> int:
            n = len(edges) + 1
            g = [[] for _ in range(n)]
            for e in edges:
                g[e[0]].append(e[1])
                g[e[1]].append(e[0])

            dia = 0
            def dfs(u:int, fa:int) -> int:
                nonlocal dia
                max_r = 0
                for v in g[u]:
                    if v == fa: continue
                    sub_r = 1 + dfs(v, u)
                    if max_r + sub_r > dia: dia = max_r + sub_r
                    if sub_r > max_r: max_r = sub_r
                return max_r
            dfs(0, -1)
            return dia
        
        dia1 = diameter(edges1)
        dia2 = diameter(edges2)
        # 三种情况的最大值， （情况3是 图1，2的半径，上取整）
        return max(dia1, dia2, 1 + (dia1+1)//2 + (dia2+1)//2)