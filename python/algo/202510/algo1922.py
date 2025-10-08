# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def countGoodNumbers(self, n: int) -> int:
        mod = 10 ** 9 + 7
        ans = pow(20, n//2, mod)
        return (ans * (5 if n%2 else 1)) % mod