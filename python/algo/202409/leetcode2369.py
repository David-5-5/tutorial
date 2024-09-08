from functools import cache
from typing import List

# 周赛 305
class Solution:
    def validPartition(self, nums: List[int]) -> bool:
        # 自行解答
        n = len(nums)
        @cache
        def dfs(i:int) -> bool:
            if i == n-3:
                if nums[i] == nums[i+1] == nums[i+2]:
                    return True
                elif nums[i] + 2 == nums[i+1] + 1 == nums[i+2]:
                    return True
                return False
            if i == n-2:
                if nums[i] == nums[i+1]: return True
                else: return False

            if i == n-1: return False
            
            if nums[i] == nums[i+1] and dfs(i+2): return True
            if (nums[i] == nums[i+1] == nums[i+2] or nums[i] + 2 == nums[i+1] + 1 == nums[i+2]) and dfs(i+3): 
                return True

            return False

        return dfs(0)

    def validPartition2(self, nums: List[int]) -> bool:
        # 自行解答, 简化
        n = len(nums)
        @cache
        def dfs(i:int) -> bool:
            if i == n: return True
            
            if i+1 < n and nums[i] == nums[i+1] and dfs(i+2): return True
            if i+2 < n and (nums[i] == nums[i+1] == nums[i+2] or nums[i] + 2 == nums[i+1] + 1 == nums[i+2]) and dfs(i+3): 
                return True

            return False

        return dfs(0)