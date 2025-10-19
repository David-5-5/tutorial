from typing import List

# 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution:
    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        # 自行解答
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