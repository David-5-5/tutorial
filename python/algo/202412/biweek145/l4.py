from bisect import bisect_right
from typing import List


class Solution:
    def countComponents(self, nums: List[int], threshold: int) -> int:
        nums.sort()
        ans = len(nums) - bisect_right(nums, threshold)
        nums = set(nums[0:len(nums) - ans])
        

        
        

if __name__ == "__main__":
    sol = Solution()

    print(sol)
