from functools import cache
from math import inf
from typing import List

# 双周赛 116
class Solution:
    def lengthOfLongestSubsequence(self, nums: List[int], target: int) -> int:
        n = len(nums)
        @cache
        def dfs(i:int, left:int) -> int:
            if i == n and left != 0: return -inf
            if left == 0:return 0

            # 不选
            res = dfs(i+1, left)
            if nums[i] <= left:
                res = max(res, 1 + dfs(i+1, left-nums[i]))
            return res
        
        ans = dfs(0, target)
        dfs.cache_clear()
        return ans if ans != -inf else -1

    def lengthOfLongestSubsequence2(self, nums: List[int], target: int) -> int:
        # 从递归改为0-1背包
        n = len(nums)
        dp = [[-inf] * (n+1) for _ in range(target+1)]
        for i in range(n+1): dp[0][i] = 0

        for i in range(1,n+1):
            for j in range(1,target+1):
                dp[j][i] = max(dp[j][i-1], 1 + dp[j-nums[i-1]][i-1] if j >= nums[i-1] else -inf)
        return max(dp[-1]) if max(dp[-1]) != -inf else -1

    def lengthOfLongestSubsequence3(self, nums: List[int], target: int) -> int:
        # 从 lengthOfLongestSubsequence2 改为 1 维
        n = len(nums)
        dp = [0] + [-inf] * target

        for i in range(n):
            for j in range(target, 0, -1):
                dp[j] = max(dp[j], 1 + dp[j-nums[i]] if j >= nums[i] else -inf)
        return dp[-1] if dp[-1] != -inf else -1


if __name__ == "__main__":
    sol = Solution()
    nums, target = [1,2,3,4,5], 9
    # nums, target = [1,1,5,4,5], 3
    nums, target = [3,5,2,3,4], 12
    print(sol.lengthOfLongestSubsequence(nums, target))
    print(sol.lengthOfLongestSubsequence3(nums, target))