class Solution:
    def lengthOfLIS(self, nums) -> int:
        n = len(nums)
        # maxLen = 1
        # maxNum = -10000
        dp = [1] * n
        for i in range(n-1, -1, -1):
            # if nums[i] > maxNum:
            #     maxNum = nums[i]
            for j in range(i+1, n):
            #     if nums[j] > maxNum:
            #         break
                if nums[i] < nums[j]:
                    dp[i] = max(dp[i], dp[j]+1)
        return max(dp)
