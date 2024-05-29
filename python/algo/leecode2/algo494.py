from typing import List
class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        # 0-1背包算法，
        # 关键在于变形，按照题意，每个数之间添加 +,- 组成表达式
        # 则添加 + 号的数之和为 p, 添加 - 号数之和为 s - p, 其中 s = sum(nums) 
        # p - (s -p ) = target -> 2p = s + target -> p = (s+t)/2 ，
        # 转换为在 nums 取若干数，其和为 (s+t)/2，使用 0-1 背包算法
        # 注 s+target 必须是偶数 且 >= 0
        s = sum(nums)
        t = (s + target) // 2
        if (s+target) % 2 == 1:return 0
        if t < 0 or target > s: return 0

        dp = [0] * (t+1)
        dp[0] = 1
        for num in nums:
            for cap in range(t, num-1,-1):
                dp[cap] += dp[cap-num]
        
        return dp[-1]

if __name__ == "__main__":
    sol = Solution()
    nums = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    print(sol.findTargetSumWays(nums,0))