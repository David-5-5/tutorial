from functools import cache
from typing import List


class Solution:
    def maxTotal(self, nums: List[int], s: str) -> int:
        # 自行解答
        n = len(nums)
        
        @cache
        def dfs(i: int, mv: bool) -> int:
            if i == n: return 0

            if s[i] == '0':
                return dfs(i+1, False)
            else:
                res = nums[i] + dfs(i+1, False) # 原地
                if mv or s[i-1] == '0':
                    res = max(res, nums[i-1] + dfs(i+1, True))
                return res
        return dfs(1, False) + (0 if s[0] == '0' else nums[0])
