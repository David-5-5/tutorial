from typing import List
from sortedcontainers import SortedList
class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        '''prefix sum & binary search
        '''
        n = len(nums)
        # The peformance is improved by using SortedList replace of 
        # list with bisect function
        sort_pres = SortedList()
        presum = ans = 0

        for i in range(n):
            # Add prevoius prefix sum into SortedList
            # The first prefix sum is 0
            sort_pres.add(presum)

            # The current prefix sum
            presum += nums[i]

            # The lower limit in SortedList, should >= presum-upper
            left = sort_pres.bisect_left(presum-upper)
            # The upper limit in SortedList, should <= presum-lower
            right = sort_pres.bisect_right(presum-lower)
            # right - left is the count of sum of sub array which in 
            # distinct [lower, upper]
            ans += right - left

        return ans
    



if __name__ == "__main__":
    sol = Solution()
    nums, lower, upper = [-2,5,-1], -2, 2
    print(sol.countRangeSum(nums, lower, upper))