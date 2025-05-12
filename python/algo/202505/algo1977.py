from functools import cache

# 动态规划 - 11.1 前缀和优化 DP
class Solution:
    def numberOfCombinations(self, num: str) -> int:
        # 自行解答 - 记忆化搜索
        mod = 10 ** 9 + 7
        n = len(num)

        @cache
        def dfs(i:int, pre:int) -> int:
            if i == n: return 1
            if num[i] == '0': return 0

            res = 0
            for j in range(max(i-pre,1), n-i+1):
                if (j == i - pre and num[i:i+j]<num[pre:i]):continue
                res += dfs(i+j,i)

            return res % mod
        return dfs(0, 0)


    def numberOfCombinations2(self, num: str) -> int:
        # 自行解答 - 递归 -> 递推
        if num[0] == '0': return 0
        mod = 10 ** 9 + 7
        n = len(num)

        dp = [[0] * (n) for _ in range(n+1)]
        for i in range(n): dp[n][i] = 1

        for i in range(n-1, -1, -1):
            if num[i] == '0':
                for j in range(n): dp[i][j] = 0
                continue
            for j in range(max(0,2*i-n), i+1):
                for k in range(max(i-j,1), n-i+1):
                    if (k == i-j and num[i:i+k]<num[j:i]):continue
                    dp[i][j] += dp[i+k][i]

        return dp[0][0] % mod

    def numberOfCombinations3(self, num: str) -> int:
        # 自行解答 - 前缀和优化
        if num[0] == '0': return 0
        mod = 10 ** 9 + 7
        n = len(num)

        dp = [[0] * (n) for _ in range(n+1)]
        for i in range(n): dp[n][i] = 1

        for i in range(n-1, -1, -1):
            if num[i] == '0':
                for j in range(n): dp[i][j] = 0
                continue
            sum = 0
            
            for k in range(i+1, n-i+1): sum += dp[i+k][i]
            for j in range(max(0,2*i-n), i+1):
                is_large = num[i:i+i-j]>=num[j:i]
                if (is_large):
                    sum += dp[i+i-j][i]
                dp[i][j] += sum
                if (not is_large):
                    sum += dp[i+i-j][i]

        return dp[0][0] % mod

if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOfCombinations("327"))