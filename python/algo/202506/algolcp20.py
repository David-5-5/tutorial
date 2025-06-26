from functools import cache
from typing import List

# 动态规划 - 专题：跳跃游戏
class Solution:
    def busRapidTransit(self, target: int, inc: int, dec: int, jump: List[int], cost: List[int]) -> int:
        # 参考题解，逆向递归
        mod = 10 ** 9 + 7
        @cache
        def dfs(pos: int) -> int:
            if pos == 0: return 0
            if pos == 1: return inc
            res = pos * inc
            for j, c in zip(jump, cost):
                prev, rem = pos // j, pos % j
                res = min(res, c + dfs(prev) + inc * rem)
                if rem:
                    res = min(res, c + dfs(prev+1) + dec * (j-rem))
            return res
        return dfs(target) % mod