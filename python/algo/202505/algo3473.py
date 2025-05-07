from cmath import inf
from functools import cache
from itertools import accumulate
from typing import List

# 动态规划 - 11.1 前缀和优化 DP
class Solution:
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        pres = list(accumulate(nums, initial = 0))
        n = len(nums)

        @cache
        def dfs(i:int, left:int) -> int:
            if n - i < left * m: return -inf  # 剪枝
            if left == 0: return # 递归结束

            res = dfs(i+1, left) # 跳过当前元素

            for k in range(m-1, n-(left-1)*m):
                val = pres[k+1]-pres[i] + dfs(i+k+1, left-1)
                if val > res: res = val
            return res
        return dfs(0, k)

