from typing import List

# 动态规划 - 爬楼梯
class Solution:
    def combinationSum4(self, nums: List[int], target: int) -> int:
        dp = [0] * (target + 1)
        dp[0] = 1
        for i in range(1, target + 1):
            for v in nums:
                if i >= v: dp[i] += dp[i-v]
        return dp[target]