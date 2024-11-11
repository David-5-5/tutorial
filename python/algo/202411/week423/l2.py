from cmath import inf
from typing import List


class Solution:
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:
        nums.append(-inf)
        n = len(nums)
        ans = prev = 1
        l = 0
        for r in range(l+1, n):
            if nums[r]>nums[r-1]:
                continue
            else:
                ans = max(ans, min(r - l, prev), (r - l) //2)
                prev = r - l
                l = r
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [5,8,-2,-1]
    print(sol.maxIncreasingSubarrays(nums))