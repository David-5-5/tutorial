class Solution:
    def waysToChange(self, n: int) -> int:
        mod = 10 ** 9 + 7
        coins = [1, 5, 10, 25]
        # 完全背包
        dp = [0] * (n+1)
        dp[0] = 1
        for coin in coins:
            for w in range(coin, n+1):
                dp[w] = (dp[w] + dp[w-coin]) % mod

        return dp[n]