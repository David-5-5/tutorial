class Solution:
    def strangePrinter(self, s: str) -> int:
        n = len(s)
        '''
        动态规划 dp[i][j] 表示 [i..j] 之间最小的打印次数，
        状态转移方程
        1) s[i]==s[j] dp[i][j] = dp[i][j-1] 也是就是打印s[i]时, 同时打印s[j]一定
           是最佳方案, 这一点不好理解
        2) s[i]!=s[j] dp[i][j] = min(dp[i][k]+dp[k+1][j])  i <= k <j
        
        Initial  dp[i][j] = 1    when i == j
                 dp[i][j] = INF  whne i != j
        '''
        dp = [[float("inf") if i != j else 1 for j in range(n)] for i in range(n)]

        # for i in range(n-2, -1, -1):
        #     for j in range(i+1, n):
        for j in range(1, n):
            for i in range(j-1, -1, -1):
                if s[i] == s[j]:
                    dp[i][j] = dp[i][j-1]
                else:
                    for k in range(i, j):
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j])
        
        return dp[0][n-1]


if __name__ == "__main__":
    sol = Solution()
    s = "aaabbb"
    print(sol.strangePrinter(s))