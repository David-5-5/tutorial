class Solution:
    def countPalindromicSubsequence(self, s: str) -> int:
        n = len(s)

    def countPalindromicSubsequence2(self, s: str) -> int:
        n = len(s)
        dp3 = [[0] * n for _ in range(n)]

        for i in range(n-3, -1, -1):
            for j in range(i+2, n):
                dp3[i][j] = dp3[i+1][j] + dp3[i][j-1] - dp3[i+1][j-1]
                if s[i] == s[j]:
                    dp3[i][j] += (j - i - 1) 
        return dp3[0][n-1]

if __name__ == "__main__":
    sol = Solution()
    s= "aabca"
    print(sol.countPalindromicSubsequence(s))        