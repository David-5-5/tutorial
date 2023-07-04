class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        dp = [[0] * n for _ in range(n)]
        dp2 = [[False] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            dp[i][i] = 1
            dp2[i][i] = True
            if (i > 0):
                dp2[i][i-1] = True
            for j in range (i+1, n):
                if dp2[i+1][j-1] and s[i] == s[j] :
                    dp2[i][j] = True
                    dp[i][j] =  dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1] + 1
                else :
                    dp2[i][j] = False
                    dp[i][j] =  dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1]
        return dp[0][n-1]
    

if __name__ == "__main__":
    sol = Solution()
    s = "aaa"
    print(sol.countSubstrings(s))