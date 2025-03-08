from functools import cache
from typing import List


class Solution:
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        n = len(days)
        
        @cache
        def dfs(i:int, v:int) -> int:
            if i == n: return 0

            if days[i] <= v: return dfs(i+1, v)
            res = costs[0] + dfs(i+1, 0)
            res = min(res, costs[1] + dfs(i+1, days[i]+6))
            res = min(res, costs[2] + dfs(i+1, days[i]+29))
            return res
        return dfs(0, 0)