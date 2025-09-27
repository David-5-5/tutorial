from math import gcd
from typing import List

#  数学算法 - 数论 - 1.6 最大公约数（GCD）
class Solution:
    def isGoodArray(self, nums: List[int]) -> bool:
        # 裴蜀定理
        return gcd(*nums) == 1