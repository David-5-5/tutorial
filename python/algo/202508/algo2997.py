
from functools import reduce
from operator import xor
from typing import List

# 位运算 - 异或（XOR）的性质
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        return (reduce(xor, nums) ^ k).bit_count()