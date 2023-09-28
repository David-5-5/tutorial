class Solution:

    def checkRecord(self, n: int) -> int:
        MOD = 10**9 + 7
        # 长度，A 的数量，结尾连续 L 的数量
        # dp[i][j][k] 表示前i天,包含j天'A',结尾连续k天'L'的数量
        dp = [[[0, 0, 0], [0, 0, 0]] for _ in range(n + 1)]
        dp[0][0][0] = 1

        for i in range(1, n + 1):
            # 以 P 结尾的数量
            for j in range(0, 2):
                for k in range(0, 3):
                    # 包含的j天'A'，末尾k天'L'清零
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % MOD
            
            # 以 A 结尾的数量
            for k in range(0, 3):
                # 末尾k天'L'清零
                dp[i][1][0] = (dp[i][1][0] + dp[i - 1][0][k]) % MOD
            
            # 以 L 结尾的数量
            for j in range(0, 2):
                for k in range(1, 3):
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1]) % MOD
        
        total = 0
        for j in range(0, 2):
            for k in range(0, 3):
                total += dp[n][j][k]
        
        return total % MOD




if __name__ == "__main__":
    sol = Solution()
    print(sol.checkRecord(5))


        
