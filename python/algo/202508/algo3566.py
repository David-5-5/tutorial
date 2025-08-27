from functools import cache, reduce
from operator import mul
from typing import List

# 回溯 - 4.2 子集型回溯
class Solution:
    def checkEqualPartitions(self, nums: List[int], target: int) -> bool:
        # 自行解答
        n = len(nums)
        
        if target*target != reduce(mul, nums): return False
        @cache
        def dfs(mask: int) -> bool:
            if mask.bit_count() == n: return False
            
            prd = 1
            for i in range(n):
                if mask >> i & 1: prd *= nums[i]
                if prd > target: return False
            
            if prd == target:return True

            for i in range(n):
                if mask >> i & 1: continue
                if (dfs(mask | 1 << i)): return True

            return False
        
        return dfs(0)