class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        dp = [[False] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            dp[i][i] = True
            if (i>0):
                dp[i][i-1] = True
            for j in range (i+1, n):
                if dp[i+1][j-1] and s[i] == s[j] :
                    dp[i][j] = True
        f = [0] * n
        
        for i in range(1, n):
            cuts = []
            for j in range(i):
                if dp[0][i]:
                    f[i] = 0
                    break
                if dp[j+1][i]:
                    cuts.append(f[j] + 1)
            if (len(cuts) > 0):
                f[i] = min(cuts)
        return f[n-1]

if __name__ == "__main__":
    sol = Solution()
    s = "aab"
    print(sol.minCut(s))