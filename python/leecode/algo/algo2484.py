class Solution:
    def countPalindromes(self, s: str) -> int:
        n = len(s)

    def countPalindromes2(self, s: str) -> int:

        n = len(s)
        dp1 = [[i-j+1 if (i>=j) else 0 for i in range(n)] for j in range(n)]
        dp3 = [[0] * n for _ in range(n)]
        dp5 = [[0] * n for _ in range(n)]

        for i in range(n-3, -1, -1):
            for j in range(i+2, n):
                dp3[i][j] = dp3[i+1][j] + dp3[i][j-1] - dp3[i+1][j-1]
                if s[i] == s[j]:
                    dp3[i][j] += dp1[i+1][j-1]

        for i in range(n-5, -1, -1):
            for j in range(i+4, n):
                dp5[i][j] = dp5[i+1][j] + dp5[i][j-1] - dp5[i+1][j-1]
                if s[i] == s[j]:
                    dp5[i][j] += dp3[i+1][j-1]

        return dp5[0][n-1] % (10 ** 9 + 7)


if __name__ == "__main__":
    sol = Solution()
    s = "000000" 
    print(sol.countPalindromes(s))