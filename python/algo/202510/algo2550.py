# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def monkeyMove(self, n: int) -> int:
        # 快速幂
        mod = 10 ** 9 + 7
        return (pow(2, n, mod) - 2) % mod