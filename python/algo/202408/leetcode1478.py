from functools import cache
from math import inf
from typing import List

# similiar to 2463
# 自行解答 动态 + 贪婪
class Solution:
    def minDistance(self, houses: List[int], k: int) -> int:
        houses.sort()
        n = len(houses)

        def distance(l:int, r:int) -> int: # 贪婪
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

if __name__ == "__main__":
    sol = Solution()
    houses, k = [1,4,8,10,20], 3
    print(sol.minDistance(houses, k))