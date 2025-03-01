from functools import cache
from math import inf
from typing import List

# 动态规划 - 约束划分个数
class Solution:
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:
        n, m = len(nums), len(andValues)

        @cache
        def dfs(i:int, j:int) -> int:
            if i == n and j == m:return 0
            if n-i < m-j or i == n or j == m:return inf
            
            res, r = inf, i
            and_ = nums[r]
            while and_ >= andValues[j]:
                if and_ == andValues[j]:
                    res = min(res, nums[r] + dfs(r+1, j+1))
                r += 1
                if r == n: break
                and_ &= nums[r]
            
            return res
        
        ans = dfs(0, 0)
        return  -1 if ans == inf else ans