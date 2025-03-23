from functools import cache
from typing import List

#  动态规划 -  状态机 DP - 基础
class Solution:
    def wiggleMaxLength(self, nums: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(i:int, p:int, inc:int):
            if (i == n): return 0

            res = dfs(i+1, p, inc)

            if p == -1:  # 未选择
                res = max(res, 1 + dfs(i+1, i, inc))
            elif inc == 0 and nums[p]!=nums[i]: # 只选了一个
                res = max(res, 1 + dfs(i+1, i, 1 if nums[i]>nums[p] else -1))
            elif inc > 0 and nums[i]<nums[p] or inc < 0 and nums[i]>nums[p]:
                res = max(res, 1 + dfs(i+1, i,  -inc))
                
            return res
        return dfs(0, -1, 0)
