from functools import reduce
from operator import xor
from typing import List

# 位运算 - 拆位 / 贡献法
class Solution:
    def getXORSum(self, arr1: List[int], arr2: List[int]) -> int:
        xor_arr2 = reduce(xor, arr2)
        return reduce(xor, map(lambda x:x&xor_arr2, arr1))
