# No. 115
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        n = len(s)
        m = len(t)
        if m > n: return 0
        dp = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(i,n):
                if s[j] == t[i]:
                    if i == 0 and j == 0:
                        dp[i][j] = 1
                    elif i == 0:
                        dp[i][j] = dp[i][j-1] + 1
                    elif dp[i-1][j-1] > 0:
                        dp[i][j] = dp[i-1][j-1] + dp[i][j-1]
                else:
                    if j > 0: dp[i][j] = dp[i][j-1]
        return dp[m-1][n-1]

if __name__ == "__main__":
    sol = Solution()
    # s = "rabbbit"
    # t = "rabbit"
    s = "babgbag"
    t = "bag"
    from datetime import datetime
    begin = datetime.now()
    print(sol.numDistinct(s,t))
    print((datetime.now()- begin).total_seconds())
