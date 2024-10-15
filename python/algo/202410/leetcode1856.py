from itertools import accumulate
from typing import List

# 与 acmcoder 上字节的笔试题相同
# 可作为模板 求子数组中 每个值作为最小值的最大区间
class Solution:
    def maxSumMinProduct(self, nums: List[int]) -> int:
        nums.append(0)
        presum = list(accumulate(nums, initial=0))

        maxArea = 0
        stack = []
        for i in range(len(nums)): # n+1 != len(nums)

            while stack and nums[stack[-1]] >= nums[i]:
                inx = stack.pop(-1)
                l = stack[-1] if stack else -1
                maxArea = max(maxArea, nums[inx] * (presum[i]- presum[l+1]))
            stack.append(i)
        return maxArea % (10 ** 9 + 7)