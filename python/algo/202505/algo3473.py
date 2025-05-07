from cmath import inf
from functools import cache
from itertools import accumulate
from typing import List

# 动态规划 - 11.1 前缀和优化 DP
class Solution:
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        pres = list(accumulate(nums, initial = 0))
        n = len(nums)

        @cache
        def dfs(i:int, left:int) -> int:
            if n - i < left * m: return -inf  # 剪枝
            if left == 0: return # 递归结束

            res = dfs(i+1, left) # 跳过当前元素

            for k in range(m-1, n-(left-1)*m):
                val = pres[k+1]-pres[i] + dfs(i+k+1, left-1)
                if val > res: res = val
            return res
        return dfs(0, k)

    def maxSum2(self, nums: List[int], k: int, m: int) -> int:
        # 参考题解，题解很清晰，还需要多训练，不用记忆化还是不熟练
        pres = list(accumulate(nums, initial = 0))
        n = len(nums)

        dp = [[0] * (n+1) for _ in range(k+1)]
        for i in range(1, k+1):
            dp[i][i * m - 1] = mx = -inf
            for j in range(i*m, n-(k-i)*m +1):
                mx = max(mx, dp[i - 1][j - m] - pres[j - m])
                dp[i][j] = max(dp[i][j-1], mx + pres[j])
        
        return dp[k][n]