from bisect import bisect_left
from typing import List

# 周赛 334
class Solution:
    def maxNumOfMarkedIndices(self, nums: List[int]) -> int:
        l, r, n = 0, len(nums) // 2, len(nums)
        nums.sort()
        ans = 0
        while l<len(nums)//2 and r < n:
            if nums[l] * 2 <= nums[r]:
                ans += 2
                r += 1
                l += 1
            else: r += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [9,2,5,4]
    print(sol.maxNumOfMarkedIndices(nums))