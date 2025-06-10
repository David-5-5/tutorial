from functools import cache
from itertools import accumulate
from math import comb
from typing import List

# 动态规划 - 15. 概率/期望 DP
class Solution:
    def getProbability(self, balls: List[int]) -> float:
        # 参考题解，会做动态规划，排列组合有点不熟悉了
        # 两个 comb 的地方参见题解
        n = len(balls)
        capacity = sum(balls) // 2
        pres = list(accumulate(balls, initial=0))

        @cache
        def dfs(i: int, s:int, c:int) -> float:
            if i == n:
                return c == 0
            left = capacity - s
            res = 0
            for j in range(max(0, left-(pres[n]-pres[i+1])), min(left, balls[i])+1):
                res += dfs(i+1, s+j, c+(j>0)-(j<balls[i])) * comb(balls[i], j)
    
            return res
        return dfs(0, 0, 0) / comb(capacity*2, capacity)
        