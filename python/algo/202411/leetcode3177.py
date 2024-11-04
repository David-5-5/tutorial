from bisect import bisect_left
from collections import defaultdict
from functools import cache
from typing import List

# 双周赛 132
class Solution:

    def maximumLength(self, nums: List[int], k: int) -> int:
        # DP 优化
        # 递归 -> 递推 -> DP 优化
        # 更改为递推的 DP 状态转移方称为
        # dp[x][j] = max(dp[x][j] + 1, dp[y][j-1] + 1 for y in set) 
        #   其中 x ! = y x = nums[i]
        # 优化后的 DP 状态转移方程为：
        # dp[x][j] = max(dp[x][j] + 1, mx[j-1]) 
        # 维护 mx[j-1] 的数组 记录 dp[y][j-1] 的最大值
        
        # ！！！代码能力仍需要提升，看着转移方程，都写不出正确有效代码！！！
        dp = defaultdict(lambda: [0] * (k + 1)) # 用 x = nums[i] 代替 i 作为状态转移方程的维度
        mx = [0] * (k+1)

        for x in nums:

            f = dp[x]
            # 倒序遍历 dp[x][j] = 1 +  mx[j-1] 是上一个元素的 j-1
            for j in range(k, -1, -1):
                f[j] += 1
                if j>0:
                    f[j] = max(f[j], mx[j-1] + 1)
                mx[j] = max(mx[j], f[j])
        return mx[k]


if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,4,5,1], 0
    nums, k = [1,2,1,1,3], 2
    nums, k = [15,6,26,32,6], 1
    print(sol.maximumLength(nums, k))