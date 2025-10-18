from math import comb
from typing import List

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def triangularSum(self, nums: List[int]) -> int:
        # 帕斯卡三角
        n, ans = len(nums), 0
        for i, v in enumerate(nums):
            ans = (ans + v * comb(n-1, i)) % 10
        return ans
