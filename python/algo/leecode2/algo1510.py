class Solution:
    def winnerSquareGame(self, n: int) -> bool:
        dp = [False] * (n+1)
        # 用 f[i] 表示先手在面对 i 颗石子时是否处于必胜态
        # 由于先手和后手都采取最优策略, 那么 f[i] 为必胜态, 当且仅当存在某个 f[i - k^2]] 为必败态。
        # 也就是说, 当先手在面对 i 颗石子时, 可以选择取走 k^2颗, 剩余的 i-k^2 颗对于后手来说是必败态, 
        # 因此先手会获胜
        for i in range(1, n+1):
            for j in range(1, n+1):
                if (j*j > i):break
                if (dp[i-j*j]) == False:
                    dp[i] = True
                    break

        return dp[n]


if __name__ == "__main__":
    sol = Solution()
    print(sol.winnerSquareGame(4))