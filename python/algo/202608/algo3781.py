import heapq
from typing import List

class Solution:
    def maximumScore(self, nums: List[int], s: str) -> int:
        pq, ans = [], 0
        for v, ch in zip(nums, s):
            heapq.heappush(pq, -v)
            if ch == '1':
                ans -= heapq.heappop(pq)
        return ans