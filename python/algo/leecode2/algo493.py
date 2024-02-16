from sortedcontainers import SortedList
from typing import List
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        n = len(nums)
        n = len(nums)
        ans = 0
        right = SortedList()
        for i in range(2, n+1):
            right.add(2 * nums[n-i+1])
            ans += right.bisect_left(nums[n-i])
        
        return ans
