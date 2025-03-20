from functools import cache
from typing import List

# 动态规划 -  多维 DP
class Solution:
    def countRoutes(self, locations: List[int], start: int, finish: int, fuel: int) -> int:
        mod = 10 ** 9 + 7
        
        @cache
        def dfs(i: int, f:int) -> int:
            if f < 0: return 0
            
            res = (i == finish)
            for j, v in enumerate(locations):
                if (j == i): continue
                res = (res + dfs(j, f - abs(locations[i] - v))) % mod
            return res

        return dfs(start, fuel)
