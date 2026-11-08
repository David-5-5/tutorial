from functools import cache
from math import inf
from typing import List

class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        # 自行解答
        @cache
        def dfs(t: int, i: int, K: int, acc: int) -> int:
            if K < 0: return inf
            if i == n-1: 
                if K == 0:
                    return t * (l - position[i-1])
                else: return inf

            res = t * (position[i] - position[i-1]) + min(
                    dfs(time[i]+acc, i+1, K, 0),
                    dfs(t, i+1, K-1, acc+time[i])
                )

            return res
        ans = dfs(time[0], 1, k, 0)
        dfs.cache_clear()
        return ans
