from functools import cache
from typing import List

# 周赛 369
class Solution:
    def minIncrementOperations(self, nums: List[int], k: int) -> int:
        # 参考题解，自行解答时，状态转移方程
        # dp[i][j] 表示 0～i之间的子数组离 i 元素有 j 个数都小于 k， 按题意 j 不超过 2
        #          的最小运算量
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0: return 0
            res = dfs(i-1, 0) + max(0, k-nums[i]) # 选择
            if nums[i] < k and j < 2:
                res = min(res, dfs(i-1,j+1))      # 补选

            return res
        return dfs(len(nums)-1, 0)