from functools import cmp_to_key
from typing import List

# 贪心专题 交换论证法
class Solution:
    def largestNumber(self, nums: List[int]) -> str:
        def func(x, y):
            sx = sy = 10
            while sx <= x: sx *= 10
            while sy <= y: sy *= 10
            return 1 if sx * y + x > sy * x + y else -1

        ans = "".join(str(v) for v in sorted(nums, key=cmp_to_key(func)))
        return ans if ans[0] != '0' else '0'

