from typing import List

# 同 713.
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        if k == 0: return 0
        ans = l = 0
        mul = 1
        for r, v in enumerate(nums):
            mul *= v
            while l <= r and mul >= k:
                mul //= nums[l]
                l += 1
            ans += r - l + 1
        return ans