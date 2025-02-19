from functools import cache
from math import inf
from typing import List

# 动态规划 - 最长公共子序列  (LCS)
class Solution:
    def maxDotProduct(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答
        @cache
        def dfs(i:int, j:int, valid:bool):
            if i < 0 or j < 0:
                if valid: return 0
                else: return -inf       # 一个都未选择，不合法
        
            res = nums1[i] * nums2[j] + dfs(i-1, j-1, True)     # 关键必选选择一个
            res = max(res, dfs(i-1, j, valid), dfs(i, j-1, valid))

            return res
        
        return dfs(len(nums1)-1, len(nums2)-1, False)