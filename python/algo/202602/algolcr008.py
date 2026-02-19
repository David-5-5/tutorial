from typing import List

class Solution:
    # 同 209. 长度最小的子数组
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
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