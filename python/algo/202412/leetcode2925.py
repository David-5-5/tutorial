from functools import cache
from typing import List

# 周赛 370
class Solution:
    def maximumScoreAfterOperations(self, edges: List[List[int]], values: List[int]) -> int:
        # 自行解答
        n = len(edges) + 1
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        @cache
        def dfs(u:int, fa:int) -> tuple[int, int]:
            cld_l = cld_r = 0
            for v in g[u]:
                if v == fa: continue
                l, r = dfs(v, u)
                cld_l += l
                cld_r += r
            if cld_l == cld_r == 0: return 0, values[u]
            return max(values[u]+cld_l, cld_r), values[u] + cld_r
            
        return dfs(0, -1)[0]        

