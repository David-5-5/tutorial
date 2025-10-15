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
        
        # 状态定义: 对于每种字母 i 当前长度 j，枚举第 i 种字母的使用数量 x
        #          其中x 的范围是 0 到 min(k, j)，即不超过 k 次且不超过当前剩余长度
        # dp[i][j] = sum(dp[i-1][j-x] * c(j,x)), where x ∈ 0~min(j,k) j ∈ 0~n
        # 初始条件: dp[0][0] = 1, 使用 0 种字母组成空字符串
        # dp[i-1][j-x]: 使用前 i-1 种字母组成长度 j-x 的方案数
        # C(j, x): 组合数，表示从 j 个位置中选 x 个放置第 i 种字母
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
        # 参考题解，生成函数，按题意完成
        if n > 26 * k:
            return 0
        if n == 0:
            return 1
        
        one_coeff = []
        # 初始化 f(t) 的初始化 0～k 系数
        for i in range(min(k,n)+1):
            one_coeff.append(inv_fac[i])
        
        coeff = [0] * (n+1)
        coeff[0] = 1
        # 计算 f(t)^26
        for _ in range(26):
            temp_coeff = [0] * (n+1)
            for e in range(0, n+1):
                for i in range(min(e, k)+1):
                    temp_coeff[e] += (one_coeff[i] * coeff[e-i]) % MOD
            coeff = temp_coeff.copy()
        
        return (fac[n] * coeff[n]) % MOD

if __name__ == "__main__":
    print(Solution().keyboard2(1, 2))