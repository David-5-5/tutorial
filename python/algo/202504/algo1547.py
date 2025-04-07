from cmath import inf
from functools import cache
from typing import List

# 动态规划 -  8.2其他区间 DP
class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        # 自行解答，记忆化搜索 O(N^3)
        # cuts.sort()

        @cache
        def dfs(i:int, j:int) -> int:

            res = inf
            for c in cuts:
                if (i < c < j):
                    res = min(res, dfs(i, c) + dfs(c, j))
            if res == inf: return 0
            res += j - i
            return res
        return dfs(0, n)