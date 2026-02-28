from cmath import inf
from functools import cache
from typing import List

# 同 256 会员题
class Solution:
    def minCost(self, costs: List[List[int]]) -> int:
        n = len(costs)

        @cache
        def dfs(i:int, prev: int) -> int:
            if i == n: return 0
            res = inf
            for color, cost in enumerate(costs[i]):
                if (color == prev): continue
                res = min(res, cost + dfs(i+1, color))
            return res

        return dfs(0, -1)