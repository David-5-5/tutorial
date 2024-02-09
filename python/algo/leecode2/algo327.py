from typing import List
from itertools import accumulate
from bisect import bisect_left, bisect_right
class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        n = len(nums)
        pres = list(accumulate(nums, initial=0))
        sort_pres = [0]

        ans = 0
        for i in range(1, n+1):
            left = bisect_left(sort_pres, pres[i]-upper)
            right = bisect_right(sort_pres, pres[i]-lower)
            ans += right - left

            inx = bisect_right(sort_pres, pres[i])
            sort_pres.insert(inx, pres[i])
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, lower, upper = [-2,5,-1], -2, 2
    print(sol.countRangeSum(nums, lower, upper))