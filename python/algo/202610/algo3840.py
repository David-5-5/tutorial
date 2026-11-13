from functools import cache
from typing import List


class Solution:
    def rob(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(i: int, prev:bool) -> int:
            if i < 0: return 0
            
            res = dfs(i-1, False)
            if not prev or colors[i] != colors[i+1]:
                res = max(res, nums[i] + dfs(i-1, True))
            return res
        return dfs(n-1, False)

    def rob2(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)

        dp = [[0, 0] for _ in range(n+1)]
        for i in range(n):
            dp[i+1][0] = max(dp[i])
            dp[i+1][1] = dp[i][0] + nums[i]
            if i and colors[i-1] != colors[i] and nums[i] + dp[i][1] > dp[i+1][1]: 
                dp[i+1][1] = nums[i] + dp[i][1]
                
        return max(dp[n])

    def rob3(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)        
        prev_0, prev_1, cur_0, cur_1 = 0, 0, 0, 0
        
        for i in range(n):
            prev_0, prev_1 = cur_0, cur_1
            cur_0 = max(prev_0, prev_1)
            cur_1 = prev_0 + nums[i]
            if i and colors[i-1] != colors[i] and nums[i] + prev_1 > cur_1: 
                cur_1 = nums[i] + prev_1
        
        return max(cur_0, cur_1)