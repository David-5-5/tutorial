from functools import cache
from math import comb

# 数学算法 - 组合数学 - 2.3 放球问题
class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        # 组合数学
        # 0 <= l1 < r1 <= l2 < r2 <= l3 <= ... <= ln_1 < rn-1 < n
        # li' = li + (i-1) ri' = ri + (i-1)
        # 0 <= l1' < r1' < l2' < r2' < l3' < ... < ln_1' < rn-1' < n
        # 即在 n + k - 1 个点中选择 2*k 个点
        mod = 10 **9 + 7
        return comb(n+k-1, k*2) % mod

    def numberOfSets2(self, n: int, k: int) -> int:
        mod = 10 **9 + 7

        # 记忆化搜索 超时
        @cache
        def dfs(i:int, j:int) -> int:
            if i < j or i < 0: return 0
            # if i == j: return 1
            if i == 0: return 1 if j == 0 else 0
            res = dfs(i-1, j) # 不选
            for k_len in range(1, i-j+2):
                res = (res + dfs(i-k_len, j-1)) % mod

            return res
        return dfs(n-1, k)

