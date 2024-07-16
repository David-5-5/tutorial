from math import gcd
from typing import List


class Solution:
    def findValidSplit(self, nums: List[int]) -> int:
        # time limit exceeded
        n = len(nums)
        suffix_product = 1
        for i in range(n):
            suffix_product *= nums[i]
        
        ans = -1
        prefix_product = 1
        for i in range(n-1):
            prefix_product *= nums[i]
            suffix_product //= nums[i]
            if gcd(prefix_product,suffix_product) == 1:
                return i

        return ans