from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        # 自行解答
        zero_cnt = l = ans = 0
        for r, v in enumerate(nums):
            if v == 0: zero_cnt += 1
            while zero_cnt > k:
                if nums[l] == 0: zero_cnt -= 1
                l += 1
            ans = max(ans, r - l + 1)
        return ans