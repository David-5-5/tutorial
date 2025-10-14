from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.2 越长越合法/求最短/最小
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        # 自行解答
        n = len(nums)
        if sum(nums) < target: return 0
        if sum(nums) == target: return n
        ans, l, acc = n, 0, 0
        for r, v in enumerate(nums):
            acc += v
            while acc >= target:
                ans = min(ans, r-l+1)
                acc -= nums[l]
                l += 1
        return ans