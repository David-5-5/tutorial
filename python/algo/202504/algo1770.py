from functools import cache
from typing import List

# 动态规划 - 8.2 其他区间 DP
class Solution:
    def maximumScore(self, nums: List[int], multipliers: List[int]) -> int:
        # 自行解答 n = len(nums)  n = 10^5
        m = len(multipliers)

        @cache
        def dfs(i:int, j:int) -> int:   # 关键是参数的选择 m 10^3
            # 避免用 n 相关参数从 0 开始从头，尾遍历 nums
            if i+j == m: return 0   # i + j == m

            mul = multipliers[i+j]
            return max(nums[i] * mul +dfs(i+1, j), nums[-j-1] * mul + dfs(i, j+1))

        return dfs(0, 0) 