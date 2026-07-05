from functools import cache


class Solution:
    func = []
    def numTrees(self, n: int) -> int:
       self.func = [0] * (n + 1)
       self.func[0] = 1
       self.func[1] = 1
       return self.doFunc(n)
       
    def doFunc(self, n: int) ->int:
        if self.func[n]!=0 :
            return self.func[n]
        total = 0
        for i in range(n):
           total += self.doFunc(i) * self.doFunc(n-1-i)
        self.func[n] = total
        return self.func[n]

    def numTrees(self, n: int) -> int:
        # 2026.7.5 复习
        @cache
        def dfs(i: int) -> int:
            if i <= 1: return 1
            res = 0
            for j in range(i):
                res += dfs(j) * dfs(i-j-1)
            return res
        return dfs(n)

    def numTrees(self, n: int) -> int:
        # 递归 -> 递推
        dp = [0] * (n+1)
        dp[0] = dp[1] = 1
        for i in range(2, n+1):
            for j in range(i):
                dp[i] += dp[j] * dp[i-j-1]
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    print(sol.numTrees(3))