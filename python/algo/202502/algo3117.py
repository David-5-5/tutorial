from functools import cache
from math import inf
from typing import List

# 动态规划 - 约束划分个数
class Solution:
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:
        n, m = len(nums), len(andValues)

        # 时间复杂度 O(n^2m) !!!overtime!!!
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


    def minimumValueSum2(self, nums: List[int], andValues: List[int]) -> int:
        # 参考题解，基于 minimumValueSum 把 and_ 放入递归参数进行累积
        # 2025.9.5 复习 性能未提升
        n, m = len(nums), len(andValues)

        # 时间复杂度 O(mnlogU) logU = 30
        @cache
        def dfs(i:int, j:int, and_: int) -> int:    # and_ 值为 logU
            if i == n and j == m:return 0
            if n-i < m-j or i == n or j == m:return inf
            
            and_ &= nums[i]
            # if (and_ < andValues[j]): return inf    # 剪枝，性能未提升
            res = dfs(i+1, j, and_)
            if (and_ == andValues[j]):
                res = min(res, dfs(i+1, j+1, -1) + nums[i])
            
            return res
        
        ans = dfs(0, 0, -1)
        return  -1 if ans == inf else ans