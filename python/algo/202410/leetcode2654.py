from math import gcd
from typing import List

# 周赛 342
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        if gcd(nums) != 1: return -1
        return 4