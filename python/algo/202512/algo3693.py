from cmath import inf
from functools import cache
from typing import List

# 动态规划 - 爬楼梯
class Solution:
    def climbStairs(self, n: int, costs: List[int]) -> int:
        # 自行解答
        @cache
        def dfs(i: int) -> int:
            if i == 0: return 0
            if i < 0: return inf
            
            return costs[i-1] + min(dfs(i-1) + 1, dfs(i-2) + 4 ,dfs(i-3) + 9)
        return dfs(n)