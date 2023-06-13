import collections

class Solution:
    def constrainedSubsetSum(self, nums, k: int) -> int:
        if len(nums) <= 1:return nums[0]
        n = len(nums)
        dp = [nums[0]] + [0 for _ in range(n-1)]
        dque = collections.deque([0])

        #ans = nums[0]
        for i in range(1, n):
            while dque and i - dque[0] > k:
                dque.popleft()
            dp[i] = max(dp[dque[0]], 0) + nums[i]
            #ans = max(ans, dp[i])
            while dque and dp[dque[-1]] < dp[i]:
                dque.pop()
            dque.append(i)
            
        return max(dp)