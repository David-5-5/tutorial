from functools import cache
from math import comb

# 数学算法 - 组合数学 - 2.3 放球问题
class Solution:
    def countVowelStrings(self, n: int) -> int:
        # 自行解答，递归
        @cache
        def dfs(prev:int, i:int) -> int:
            if i == 0: return 1
            
            res = 0
            for j in range(prev, 5):
                res += dfs(j, i-1)
            return res
        return dfs(0, n)

    def countVowelStrings(self, n: int) -> int:
        # 递归 -> 递推 二维优化到一维
        dp = [1] * 5
        for _ in range(n-1):
            for j in range(1, 5):
                dp[j] += dp[j-1]
        return sum(dp)

    def countVowelStrings(self, n: int) -> int:
        # 参考题解 - 组合数学
        return comb(n+4, 4)