from functools import cache
from math import inf
from typing import List

# 动态规划 - 最长公共子序列  (LCS)
class Solution:
    def maxScore(self, a: List[int], b: List[int]) -> int:
         
        n = len(b)
        @cache
        def dfs(i:int, j:int) -> int:
            if j < i : return -inf
            if i == 0: return 0

            return max(dfs(i-1,j-1) + a[i-1]*b[j-1], dfs(i,j-1))
        
        return dfs(4, n)