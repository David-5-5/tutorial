MOD = 1_000_000_007
MX = 500_001

# 组合数模板 组合数 求 逆元 
# replace math.comb
fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % MOD

def comb(n: int, k: int) -> int:
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD

class Solution:
    def countValidSequences(self, n: int, k: int) -> int:
        mod = 10 ** 9 + 7
        if n <= k: return 0
        if (n % 2) ^ (k % 2):
            return comb(n-1, k-1) % mod
        else:
            # comb(n-1, k-1) 减去全是奇数的情况
            # 全是奇数的情况下：
            # n = x1 + x2 + ... + xk  xi都是奇数
            #   = y1 * 2 -1 + y2 * 2 -1 + ... + yk * 2 -1 
            # (n + k)/2 = y1 + y2 + ... + yk
            # 即将 (n + k)/2 分为 k 个数的组合数
            return (comb(n-1, k-1) - comb((n+k)//2-1, k-1)) % mod
