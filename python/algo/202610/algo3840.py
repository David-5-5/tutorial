from functools import cache
from typing import List


class Solution:
    def rob(self, nums: List[int], colors: List[int]) -> int:
        n = len(nums)

        @cache
        def dfs(i: int, prev:bool) -> int:
            if i < 0: return 0
            
            res = dfs(i-1, False)
            if not prev or colors[i] != colors[i+1]:
                res = max(res, nums[i] + dfs(i-1, True))
            return res
        return dfs(n-1, False)

