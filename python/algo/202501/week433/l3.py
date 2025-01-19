from functools import cache
from math import inf
from typing import List

# 3428
class Solution:
    def minCost(self, n: int, cost: List[List[int]]) -> int:
        # 动态规划，应该能做出来，被上题搞崩溃了

        @cache
        def dfs(i:int, pre_i:int,  pre_j:int) -> int:
            if i >= n // 2: return 0

            res = inf
            for sel_i, c_i in enumerate(cost[i]):
                if sel_i == pre_i:continue
                for sel_j, c_j in enumerate(cost[-i-1]):
                    if sel_j != sel_i and sel_j != pre_j:
                        res = min(res, c_i + c_j + dfs(i+1, sel_i, sel_j))
            return res
        

        return dfs(0, 4, 4)