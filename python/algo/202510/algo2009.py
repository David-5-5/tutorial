from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        # 参考题解 - 没有思路像座大山
        # 排序去重，窗口中的最大值-最小值不超过 n-1，
        # 减去窗口中能包含的最大数量，就是需要改变的最小数量（其他值需要修改）
        l, n = 0, len(nums)
        ans = n - 1
        nums = sorted(set(nums))
        for r, v in enumerate(nums):
            while v-nums[l]+1 > n:
                l += 1
            ans = min(ans, n - 1 + l - r)
        return ans  