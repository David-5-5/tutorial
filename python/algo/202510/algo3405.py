# 数学算法 - 组合数学 - 2.2 组合计数
from math import comb

MOD = 1_000_000_007
# MX = 100_000

# fac = [0] * MX
# fac[0] = 1
# for i in range(1, MX):
#     fac[i] = fac[i - 1] * i % MOD

# inv_fac = [0] * MX
# inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)
# for i in range(MX - 1, 0, -1):
#     inv_fac[i - 1] = inv_fac[i] * i % MOD

# def comb(n: int, k: int) -> int:
#     return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD

class Solution:
    def countGoodArrays(self, n: int, m: int, k: int) -> int:
        return comb(n-1,k) % MOD * m * pow(m-1, n-k-1, MOD) % MOD