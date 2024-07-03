from  typing import List
from itertools import accumulate
# 划分型 DP
# 暴力思路，从最后一个子数组思考，按题意 求 dp[i][j] 状态转移的最大值
# 状态方程应该是二维的 dp[i][j] 表示前 j 个元素划分为 i 个子树组
# 最后一个元素 ： 选/不选
# 不选的话，可以转移到前 j-1 个元素划分为 i 个子树组即 dp[i][j] = dp[i][j-1]
# 选的话，dp[i][j] = dp[i-1][j-1] + sum[j..j] * w_i
# 从末尾开始，可以选几个 ... p 个
# dp[i][j] = dp[i-1][j-2] + sum[j-1..j] * w_i
# ...
# dp[i][j] = dp[i-1][j-p] + sum[j-p+1..j] * w_i
# 转移到其中的最大值
# 暴力三重循环
# for i in range(1, k+1):
#   for j in range(i,n+1):
#       for l in range(i,j):
#           dp[i][j] = max(dp[i][j-1], dp[i-1][j-l] + sum[j-l+1..j] * w_i)
# 优化：
# 记住 j 每次的max最大值
# max(dp[i][j-1], dp[i-1][j-l] + sum[j-l+1..j] * w_i)

class Solution:
    def maximumStrength(self, nums: List[int], k: int) -> int:
        n = len(nums)

        s = list(accumulate(nums, initial=0))
        dp = [[0] * (n+1) for _ in range(k+1)]
        for i in range(1, k+1):
            dp[i][i-1] = mx = - float("inf")
            w = (1 if (i+1) % 2 == 0 else -1) * (k-i+1)
            for j in range(i, n+1):
                mx = max(mx, dp[i-1][j-1] - s[j-1] * w)
                dp[i][j] = max(dp[i][j-1], s[j] * w + mx)
                
        return dp[k][n]

    # 二维 -> 一维 
    def maximumStrength2(self, nums: List[int], k: int) -> int:
        n = len(nums)

        s = list(accumulate(nums, initial=0))
        dp = [0] * (n+1)
        for i in range(1, k+1):
            prev = dp[i-1]
            dp[i-1] = mx = - float("inf")
            w = (1 if (i+1) % 2 == 0 else -1) * (k-i+1)
            for j in range(i, n+1):                
                mx = max(mx, prev - s[j-1] * w) # prev 替换 dp[i-1][j-1] j从 i开始循环，因此prev 初始为i-1
                prev = dp[j]                    # 提供给下一次循环使用
                dp[j] = max(dp[j-1], s[j] * w + mx)
                
        return dp[n]

    # 去掉低效的max函数 
    def maximumStrength3(self, nums: List[int], k: int) -> int:
        n = len(nums)

        s = list(accumulate(nums, initial=0))
        dp = [0] * (n+1)
        for i in range(1, k+1):
            prev = dp[i-1]
            dp[i-1] = mx = - float("inf")
            w = (1 if (i+1) % 2 == 0 else -1) * (k-i+1)
            for j in range(i, n+1):

                mx = mx if mx > prev - s[j-1] * w else prev - s[j-1] * w
                prev = dp[j]                  
                dp[j] = dp[j-1] if dp[j-1]>s[j] * w + mx else s[j] * w + mx
                
        return dp[n]

    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,-1,2], 3
    print(sol.maximumStrength(nums, k))
    print(sol.maximumStrength3(nums, k))