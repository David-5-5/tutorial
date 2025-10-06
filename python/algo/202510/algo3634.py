from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def minRemoval(self, nums: List[int], k: int) -> int:
        # 自行解答，排序后，计算子数组的最大长度
        nums.sort()

        mx_substr = l =  0
        for r, v in enumerate(nums):
            while nums[l] * k < v:
                l += 1
            mx_substr = max(mx_substr, r - l + 1)
        return len(nums) - mx_substr    # 数组长度 - 最大子数组长度
