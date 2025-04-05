from functools import cache
from typing import List

# 动态规划 - 8.2 其他区间 DP
class Solution:
    def maximumScore(self, nums: List[int], multipliers: List[int]) -> int:
        # 自行解答
        m = len(multipliers)

        @cache
        def dfs(i:int, j:int) -> int:
            if i+j == m: return 0

            mul = multipliers[i+j]
            return max(nums[i] * mul +dfs(i+1, j), nums[-j-1] * mul + dfs(i, j+1))

        return dfs(0, 0) 