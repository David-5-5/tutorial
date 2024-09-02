# 双周赛 117
class Solution:
    def stringCount(self, n: int) -> int:
        # 组合数学 - 容斥原理
        # 所有方案数 - 不合格方案数
        # 所有方案数 26 ^ n, 每个字符取任意26个字母其中一个
        # 不合格方案数：
        # 集合 A 不包含 l 25 ^ n
        # 集合 B 不包含 t 25 ^ n
        # 集合 C 不包含 e 或 仅包含一个 e 25 ^ n + n * 25 ^ (n-1)
        # 集合 A ∩ B 24 ^ n
        # 集合 A ∩ C 24 ^ n + n * 24 ^ (n-1)
        # 集合 B ∩ C 24 ^ n + n * 24 ^ (n-1)
        # 集合 A ∩ B ∩ C 23 ^ n + n * 23 ^ (n-1) = (n+23)*23^(n-1)
        # 简化:
        # A + B + C = (75 + n) * 25 ^ (n-1)
        # A ∩ B + A ∩ C + B ∩ C = (72 + 2n) * 24 ^ (n-1)
        MOD = 10 ** 9 + 7
        ans = pow(26, n, MOD)
        ans -= (75+n) * pow(25,n-1, MOD)
        ans += (72+2*n) * pow(24,n-1,MOD)
        ans -= (n+23) * pow(23,n-1,MOD)
        return ans % MOD
    
