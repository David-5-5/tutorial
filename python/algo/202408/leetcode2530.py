
import heapq
from typing import List

class Solution:
    def maxKelements(self, nums: List[int], k: int) -> int:
        for i in range(len(nums)):
            nums[i] = -nums[i]
        heapq.heapify(nums)
        ans = 0

        for _ in range(k):
            ans -= heapq.heapreplace(nums, nums[0] // 3)
        return ans