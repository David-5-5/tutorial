from typing import List
class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        # 同 494
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