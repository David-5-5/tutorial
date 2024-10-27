from math import gcd, lcm
from typing import List


class Solution:
    def maxScore(self, nums: List[int]) -> int:
        ans = gcd(*nums) * lcm(*nums)

        if len(nums) == 1: return ans

        for i in range(len(nums)):
            sub  = nums[0:i]+nums[i+1:]
            ans = max(ans, gcd(*sub) * lcm(*sub))
        
        return ans