class Solution:
    def maxPalindromes(self, s: str, k: int) -> int:
        # 动态规划
        # dp[i] 表示 i-1 之前的回文串的数目
        n = len(s)
        dp = [0] * (n + 1)
        for i in range(1, n+1):
            dp[i] = max(dp[i-1],dp[i]) # 不选
            d1 = 0
            while 0 <= (i-1) - d1 and (i-1) + d1 < n and s[(i-1) - d1] == s[(i-1) + d1]:
                d1 += 1
                if (2 * d1)-1 >= k:
                    dp[i - 1 + d1] = max(dp[i -1 + d1], 1 + dp[i - d1])
            
            d2 = 0
            while 0 <= (i-1) - d2 - 1 and (i-1) + d2 < n and s[(i-1) - d2 - 1] == s[(i-1) + d2]:
                d2 += 1
                if (2 * d2) >= k:
                    dp[i + d2 - 1] = max(dp[i + d2-1], 1 + dp[i - d2 -1])
            
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    s, k = "abaccdbbd", 3
    print(sol.maxPalindromes(s, k))