from typing import List
from sortedcontainers import SortedList
class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        n = len(nums)
        sort_pres = SortedList()
        presum = ans = 0

        for i in range(n):
            sort_pres.add(presum)
            presum += nums[i]

            left = sort_pres.bisect_left(presum-upper)
            right = sort_pres.bisect_right(presum-lower)
            ans += right - left

        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, lower, upper = [-2,5,-1], -2, 2
    print(sol.countRangeSum(nums, lower, upper))