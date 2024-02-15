from sortedcontainers import SortedList
from typing import List
class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        n = len(nums)
        count = [0] * n
        right = SortedList()
        for i in range(2, n+1):
            right.add(nums[n-i+1])
            count[n-i] = right.bisect_left(nums[n-i])
        
        return count
