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

    def numberOfSets2(self, n: int, k: int) -> int:
        mod = 10 **9 + 7

        # 记忆化搜索 超时
        @cache
        def dfs(i:int, j:int) -> int:
            if i < j or i < 0: return 0
            # if i == j: return 1
            if i == 0: return 1 if j == 0 else 0
            res = dfs(i-1, j) # 不选
            for k_len in range(1, i-j+2):
                res = (res + dfs(i-k_len, j-1)) % mod

            return res
        return dfs(n-1, k)

    def numberOfSets3(self, n: int, k: int) -> int:
        # 递归 -> 递推
        mod = 10 **9 + 7
        dp = [[0]*(k+1) for _ in range(n)]
        dp[0][0] = 1

        # 动态规划 超时
        for i in range(1, n):
            dp[i][0] = 1 # 设置为 1, j 从 1..k 开始
            for j in range(1, k+1):
                dp[i][j] = dp[i-1][j]       # 不选
                max_k = i-j+2
                for k_len in range(1, max_k):
                    dp[i][j] += dp[i-k_len][j-1]
                dp[i][j] %= mod

        return dp[n-1][k]

    def numberOfSets4(self, n: int, k: int) -> int:
        # 递归 -> 递推 - 前缀和优化
        mod = 10 **9 + 7
        dp = [[0]*(k+1) for _ in range(n)]
        dp[0][0] = 1

        # 动态规划 - 通过
        pres = [0] * k      # 按 k 设置前缀和
        for i in range(1, n):
            dp[i][0] = 1 # 设置为 1, j 从 1..k 开始
            for j in range(1, k+1):
                if i < j: continue
                dp[i][j] = dp[i-1][j]       # 不选
                pres[j-1] += dp[i-1][j-1]
                if j-2>= 0: pres[j-1] -= dp[j-2][j-1]
                dp[i][j] = (dp[i][j] + pres[j-1]) % mod

        return dp[n-1][k]