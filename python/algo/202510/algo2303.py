from typing import List

# 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        
        l = ans = total = 0
        for r, v in enumerate(nums):
            total += v
            while total * (r-l+1) >= k:
                total -= nums[l]
                l += 1
            ans += r - l + 1
        return ans        