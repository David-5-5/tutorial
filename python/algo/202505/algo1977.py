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



if __name__ == "__main__":
    sol = Solution()
    print(sol.numberOfCombinations("327"))