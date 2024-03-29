class Solution:
    def maxSizeSlices(self, slices) -> int:
        def calculate(s):
            n = len(s)
            choose = (n + 1) // 3
            dp = [[0] * (choose + 1) for _ in range(n + 1)]
            for i in range(1, n + 1):
                for j in range(1, choose + 1):
                    dp[i][j] = max(dp[i - 1][j], (dp[i - 2][j - 1] if i - 2 >= 0 else 0) + s[i - 1])
            return dp[n][choose]

        ans1 = calculate(slices[1:])
        ans2 = calculate(slices[:-1])
        return max(ans1, ans2)

if __name__ == "__main__":
    sol = Solution()
    slices = [9,8,1,7,7,9,5,10,7,9,3,8,3,4,8]
    print(sol.maxSizeSlices(slices))
