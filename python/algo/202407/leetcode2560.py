from bisect import bisect_left
from functools import cache
from typing import List
# 周赛 331 二分查找，自行解答
class Solution:
    # 二分查找，自行解答，贪心
    def minCapability(self, nums: List[int], k: int) -> int:
        right = max(nums) # + 1

        def check(mn:int) -> bool:
            # mn += 1
            prev, cnt = -2, 0
            for i, v in enumerate(nums):
                if v <= mn and i - 1 > prev:
                    cnt += 1
                    prev = i
                if cnt == k: return True
            return False

        return bisect_left(range(right), True, key=check)

    # 参考视频 二分查找 DP
    def minCapability2(self, nums: List[int], k: int) -> int:
        right = max(nums) # + 1
        n = len((nums))

        def check(mn:int) -> int:
            dp = [0] * (n+1)
            for i, v in enumerate(nums):
                if mn >= v:
                    dp[i+1] = max(dp[i], 1 + (dp[i-1] if i >= 1 else 0))
                else:
                    dp[i+1] = dp[i]

            return dp[n]
            # 仅使用 dp0 和 dp1 两个变量
            # dp0 = dp1 = 0
            # for i, v in enumerate(nums):
            #     dp = 0
            #     if mn >= v:
            #         dp = max(dp1, 1 + dp0)
            #     else:
            #         dp = dp1
            #     dp0, dp1 = dp1, dp

            # return dp1        

            
        return bisect_left(range(right), k, key=check)

if __name__ == "__main__":
    nums, k = [2,3,5,9], 2
    nums, k = [2,7,9,3,1], 2
    sol = Solution()
    print(sol.minCapability(nums, k))
    print(sol.minCapability2(nums, k))    