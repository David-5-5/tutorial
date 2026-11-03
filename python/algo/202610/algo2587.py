from itertools import accumulate
from typing import List

class Solution:
    def maxScore(self, nums: List[int]) -> int:
        nums.sort(reverse=True)
        pres = list(accumulate(nums))

        return len([v for v in pres if v > 0])