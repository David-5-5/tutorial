from functools import cache
from typing import List

# 周赛 370
class Solution:
    def maximumScoreAfterOperations(self, edges: List[List[int]], values: List[int]) -> int:
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        # @cache
        # def dfs(u:int, fa:int, not_zero:bool) -> tuple[int, int]:
            
        #     if not_zero:
        #         val = values[u] # 加入分数
        #         for v in g[u]:
        #             if v == fa:continue
        #             val += dfs(v, u, not_zero)
        #         return val
        #     else:
        #         if len(g[u]) == 0 or (len(g[u]) == 1 and g[0] == fa):
        #             return 0 # 叶子节点，保留在树上
                
        #         val1 = values[u] # 加入分数
        #         for v in g[u]:
        #             if v == fa:continue
        #             val1 += dfs(v, u, not_zero)

        #         val2 = 0 # 保留在树上
        #         for v in g[u]:
        #             if v == fa:continue
        #             val2 += dfs(v, u, True)
        #         return max(val1, val2)
        
        # return dfs(0, -1, False)
        
        @cache
        def dfs(u:int, fa:int, left:bool) -> tuple[int, int]:
            # 父节点留在树上
            if left:
                val1 = values[u]
                val2 = 0
                for v in g[u]:
                    if v == fa:continue
                    v1, v2 = dfs(v, u, True)
                    val1 += v1
                    val2 += v2
                return val1, val2
            else: # 父节点加入分数
                # 本节点留在树上
                val1 = 0
                val2 = 0
                for v in g[u]:
                    if v == fa:continue
                    v1, v2 = dfs(v, u, True)
                    val1 += v1
                    val2 += v2
                # 本节点收获
                val1 = 0
                val2 = 0
                for v in g[u]:
                    if v == fa:continue
                    v1, v2 = dfs(v, u, False)
                    val1 += v1
                    val2 += v2


        return max(dfs(0, -1))


