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

