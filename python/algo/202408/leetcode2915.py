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
    
if __name__ == "__main__":
    sol = Solution()
    nums, target = [1,2,3,4,5], 9
    nums, target = [1,1,5,4,5], 3
    print(sol.lengthOfLongestSubsequence(nums, target))