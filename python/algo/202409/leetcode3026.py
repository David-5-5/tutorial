from cmath import inf
from itertools import accumulate
from typing import List

# 双周赛 123
class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        presum = list(accumulate(nums, initial=0))

        ans, n = -inf, len(nums)
        
        s_nums = sorted(enumerate(nums), key=lambda p:p[1])
        l = r = 0
        while l < n and r < n:
            if s_nums[r][1] - s_nums[l][1] == k:
                while l+1 < n and s_nums[l][1] == s_nums[l+1][1] and (s_nums[l][1] <= 0 and s_nums[l][0]<s_nums[r][0] or s_nums[l][1] > 0 and s_nums[l][0]>s_nums[r][0] ):
                    l += 1
                while r+1 < n and s_nums[r][1] == s_nums[r+1][1] and (s_nums[r][1] >= 0 and s_nums[l][0]<s_nums[r][0] or s_nums[r][1] < 0 and s_nums[l][0]>s_nums[r][0] ):
                    r += 1
                end = max(s_nums[r][0], s_nums[l][0]) + 1
                begin = min(s_nums[r][0], s_nums[l][0])                
                if presum[end] - presum[begin] > ans:
                    ans = presum[end] - presum[begin]
                
                while l+1 < n and s_nums[l][0] == s_nums[l+1][0]: l += 1
                while r+1 < n and s_nums[r][0] == s_nums[r+1][0]: r += 1
                l += 1
                r += 1
            
            if r < n and s_nums[r][1] - s_nums[l][1] > k:
                l += 1
            elif r < n and s_nums[r][1] - s_nums[l][1] < k:
                r += 1

        return 0 if ans == -inf else ans 


if __name__ == "__main__":
    sol = Solution()
    nums, k  = [-1,3,2,4,5], 3
    nums, k  = [5,3,3],2
    print(sol.maximumSubarraySum(nums,k))