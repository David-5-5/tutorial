MOD = 1_000_000_007
MX = 100

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

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def keyboard(self, k: int, n: int) -> int:
        # 参考题解，先提交代码，再继续研究 生成函数 <-> 动态规划
        if n > 26 * k:
            return 0
        if n == 0:
            return 1
        
        for _ in range(26):
            new_dp = [0] * (n + 1)
            for j in range(n + 1):
                for l in range(0, min(j, k) + 1):
                    new_dp[j] = (new_dp[j] + dp[j - l] * inv_fac[l]) % MOD
            dp = new_dp
        
        fact_n = 1
        for i in range(1, n + 1):
            fact_n = fact_n * i % MOD
        return fact_n * dp[n] % MOD

    def keyboard2(self, k: int, n: int) -> int:
        
