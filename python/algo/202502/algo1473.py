from cmath import inf
from functools import cache
from typing import List

# 动态规划 - 约束划分个数
class Solution:
    def minCost(self, houses: List[int], cost: List[List[int]], m: int, n: int, target: int) -> int:
        m = len(houses)

        @cache
        def dfs(i:int, prev:int, left:int) -> int:
            if left < 0: return inf
            if i < 0:
                if left == 0: return 0
                else: return inf

            if (houses[i]!=0): return dfs(i-1, houses[i], left-(prev!=houses[i]))
            
            res = inf
            for c in range(1, n+1):
                res = min(res, cost[i][c-1] + dfs(i-1, c, left-(prev!=c)))
            return res
        
        ans = dfs(m-1, 0, target)
        return -1 if ans == inf else ans
            