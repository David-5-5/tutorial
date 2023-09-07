class Solution:
    def countPalindromicSubsequences(self, s: str) -> int:
        MOD = 10 ** 9 + 7
        n = len(s)
        # State dp (x, i, j) represents the total number of different
        # palindrome sequences starting and ending with the character x 
        # in the string interval s [i: j], where s [i: j] represents the
        # substring of from i to j (include i, j).
        # Thus the result is sum(dp(x , 0, n-1)), which x in (a, b, c, d)
        # There are four situation:
        # 1) When s [i]=x and s [j]=x, adding the character x at the beginning
        #    and end of any "palindrome sequence" in s [i+1: j-1] will generate
        #    a new "palindrome sequence"
        #       dp (x, i, j)=2+sum (dp (c, i+1, j-1)) which c in (a, b, c, d)
        # 2) When s[i]=x and s[j]≠x, dp (x, i, j) = dp (x, i, j-1)
        # 3) When s[i]≠x and s[j]=x, dp (x, i, j) = dp (x, i+1, j)
        # 4) When s[i]≠x and s[j]≠x, dp (x, i, j) = dp (x, i+1, j-1)
        # And the dp initialze
        # dp[c][i][j] = 
        #   1,  if i == j and s[i] == c
        #   0,  else
        dp = [[[1 if i==j and s[i] == chr(ord('a')+c) else 0 for i in range(n)] for j in range(n)] for c in range(4)]


        for j in range(1, n):
            for i in range(j-1, -1, -1):
                for k, c in enumerate("abcd"):
                    if s[i] == s[j] == c:
                        # situation 1:
                        dp[k][i][j] = (dp[0][i+1][j-1] + dp[1][i+1][j-1] + dp[2][i+1][j-1] + dp[3][i+1][j-1] + 2) % MOD
                    elif s[i] == c:
                        # situation 2:
                        dp[k][i][j] = dp[k][i][j-1]
                    elif s[j] == c:
                        # situation 3:
                        dp[k][i][j] = dp[k][i+1][j]
                    else:
                        # situation 4:
                        dp[k][i][j] = dp[k][i+1][j-1]
        
        return (dp[0][0][n-1] + dp[1][0][n-1] + dp[2][0][n-1] + dp[3][0][n-1]) % MOD

if __name__ == "__main__":
    sol = Solution()
    s = 'bccb'
    # s = "aab"
    print(sol.countPalindromicSubsequences(s))