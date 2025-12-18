# 杂项 - 7.2 整数拆分

class Solution:
    def maxNiceDivisors(self, primeFactors: int) -> int:
        mod = 10**9 + 7
        ans = 1
        # 遍历 k 从 2 到 primeFactors（包含）
        if primeFactors < 5: return primeFactors
        expo = primeFactors // 3  # 整除，对应 C++ 的 /（int 除法）
        rem = primeFactors % 3    # 取余
        if rem == 0: rem = 1
        elif rem == 1:
            expo -= 1
            rem = 4
        res = pow(3, expo, mod) * rem % mod

        # 返回结果取模
        return res      