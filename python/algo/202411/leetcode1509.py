from typing import List

# 贪心专题
class Solution:
    def minDifference(self, nums: List[int]) -> int:
        if len(nums) <= 4: return 0
        nums.sort() # 排序
        # 4种组合： 最小/大值 3/0, 2/1, 1/2, 0/3
        # 求种情况的修改后的最小值
        return min(nums[-4]-nums[0], nums[-3]-nums[1], nums[-2]-nums[2], nums[-1]-nums[3])