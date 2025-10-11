from typing import List


# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        # 自行解答 - 滑动窗口
        ans, l, n = 1, 0, len(nums)
        nums.sort()

        for r, v in enumerate(nums):
            if r == 0: continue
            k -= (r - l) * (v-nums[r-1])
            while l < n and k < 0:
                k += v - nums[l]
                l += 1
            ans = max(ans, r - l  + 1)
        return ans