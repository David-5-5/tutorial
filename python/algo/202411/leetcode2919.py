from functools import cache
from typing import List

# 周赛 369
class Solution:
    def minIncrementOperations(self, nums: List[int], k: int) -> int:
        # 参考题解，自行解答时，状态转移方程
        # dp[i][j] 表示 0～i之间的子数组离 i 元素有 j 个数都小于 k， 按题意 j 不超过 2
        #          的最小运算量
        @cache
        def dfs(i:int, j:int) -> int:
            if i < 0: return 0
            res = dfs(i-1, 0) + max(0, k-nums[i]) # 选择
            if nums[i] < k and j < 2:
                res = min(res, dfs(i-1,j+1))      # 不选

            return res
        return dfs(len(nums)-1, 0)

    def minIncrementOperations2(self, nums: List[int], k: int) -> int:
        # 递归 -> 递推
        n = len(nums)

        dp = [[0] * 3 for i in range(n+1)]
        for i in range(n):
            for j in range(3):
                dp[i+1][j] = dp[i][0] + max(0, k-nums[i])
                if j < 2:
                    dp[i+1][j] = min(dp[i+1][j], dp[i][j+1])
        return dp[n][0]

    def minIncrementOperations3(self, nums: List[int], k: int) -> int:
        # 递推 空间优化

        f0 = f1 = f2 = 0
        for x in nums:
            inc = f0 + max(k-x, 0)
            f0 = min(inc, f1)
            f1 = min(inc, f2)
            f2 = inc
        return f0

if __name__ == "__main__":
    sol = Solution()
    nums, k = [2,3,0,0,2], 4
    print(sol.minIncrementOperations3(nums,k))