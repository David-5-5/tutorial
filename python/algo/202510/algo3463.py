from math import comb
from typing import List

MOD = 10
MX = 100_000
POW2 = (2, 4, 8, 6)

f = [0] * (MX + 1)
inv_f = [0] * (MX + 1)
p2 = [0] * (MX + 1)
p5 = [0] * (MX + 1)

f[0] = inv_f[0] = 1
for i in range(1, MX + 1):
    x = i
    # 计算 2 的幂次
    e2 = (x & -x).bit_length() - 1
    x >>= e2
    # 计算 5 的幂次
    e5 = 0
    while x % 5 == 0:
        e5 += 1
        x //= 5
    f[i] = f[i - 1] * x % MOD
    inv_f[i] = pow(f[i], 3, MOD)  # 欧拉定理求逆元
    p2[i] = p2[i - 1] + e2
    p5[i] = p5[i - 1] + e5

def comb(n: int, k: int) -> int:
    e2 = p2[n] - p2[k] - p2[n - k]
    return f[n] * inv_f[k] * inv_f[n - k] * \
        (POW2[(e2 - 1) % 4] if e2 else 1) * \
        (5 if p5[n] - p5[k] - p5[n - k] else 1)


# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def hasSameDigits(self, s: str) -> bool:
        # 帕斯卡三角
        n, ans1, ans2 = len(s), 0, 0
        for i, v in enumerate(s[0:n-1]):
            ans1 = (ans1 + (ord(v)-ord('0')) * comb(n-2, i) ) % 10
        for i, v in enumerate(s[1:]):
            ans2 = (ans2 + (ord(v)-ord('0')) * comb(n-2, i) ) % 10

        return ans1 == ans2