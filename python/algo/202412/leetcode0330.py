from typing import List

# 贪心专题 - 归纳法
# 同 2952
class Solution:
    def minPatches(self, nums: List[int], n: int) -> int:
        nums.sort()
        ans, x, l, m = 0, 1, 0, len(nums)

        while x <= n: # x-1 在数组中，x 不在数组中
            if l < m and nums[l] <= x:
                x += nums[l]
                l += 1
            else:
                ans += 1
                x <<= 1
        return ans