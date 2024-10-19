from cmath import inf
from functools import cache


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

    def minCut2(self, s: str) -> int:
        # 子集型 记忆化 搜索
        n = len(s)
        # The preprocessing of palindrome
        isPal = [[False] * n for _ in range(n)]
        for i in range(n-1, -1, -1):
            isPal[i][i] = True
            if (i>0):
                isPal[i][i-1] = True
            for j in range (i+1, n):
                if isPal[i+1][j-1] and s[i] == s[j] :
                    isPal[i][j] = True

        @cache
        def dfs(i:int) -> int:
            if i == n:
                return -1

            res = inf
            for j in range(i,n):
                # t = s[i:j+1]
                # if t == t[::-1]:
                # replace string compare of palindrome by isPalindrome preprocessing
                if isPal[i][j]:
                    res = min(res, 1+dfs(j+1))
            return res
        return dfs(0)

    def minCut3(self, s: str) -> int:
        # 记忆化搜索 -> 递推
        n = len(s)

        dp = [inf] * (n+1)
        dp[n] = -1

        for i in range(n, -1, -1):
            for j in range(i, n):
                t = s[i:j+1]
                if t == t[::-1]:
                    dp[i] = min(dp[i], 1+dp[j+1])
        return dp[0]

if __name__ == "__main__":
    sol = Solution()
    s = "aab"
    print(sol.minCut(s))
    print(sol.minCut3(s))