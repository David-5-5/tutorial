from functools import cache
from math import inf
from typing import List

# similiar to 2463
# 自行解答
class Solution:
    def minDistance(self, houses: List[int], k: int) -> int:
        houses.sort()
        n = len(houses)

        def distance(l:int, r:int) -> int:
            res = 0
            mid = (l + r) // 2
            for i in range(l, r+1):
                res += abs(houses[i]-houses[mid])
            return res

        @cache
        def dfs(i:int, j:int) -> int:
            if j == 1:
                return distance(i, n-1)

            res = inf
            for k in range(i, n-j+1):
                res = min(res, distance(i, k) + dfs(k+1, j-1))

            return res

        return dfs(0, k)