from itertools import combinations_with_replacement
from math import factorial
from typing import Counter, List

# 数学算法 - 概率期望
class Solution:
    def statisticsProbability(self, num: int) -> List[float]:
        # 自行解答 - 使用 combinations_with_replacement 枚举组合
        fact = factorial(num)
        deno = 6 ** num
        result = [0] * (5*num + 1)
        for res in combinations_with_replacement(range(1, 7), num):
            tot = sum(res)
            cnt = Counter(res)
            prem = fact
            for v in cnt.values():
                prem /= factorial(v)
            result[tot-num] += prem / deno

        return result