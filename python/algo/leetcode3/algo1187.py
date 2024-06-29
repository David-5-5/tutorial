from bisect import bisect_right
from functools import lru_cache
from math import inf
from typing import List

class Solution:
    def makeArrayIncreasing(self, arr1: List[int], arr2: List[int]) -> int:
        n = len(arr1)
        m = len(arr2)
        arr2.sort()

        @lru_cache(maxsize=None)
        def dfs(i, prev):
            if i == n:
                return 0

            res = inf
            # not select, just not change
            if arr1[i] > prev:
                res = dfs(i+1, arr1[i])

            inx = bisect_right(arr2, prev)
            if inx < m:
                res = min(res, dfs(i+1, arr2[inx])+1)
            # elif prev >= arr1[i]:
            #     return inf

            return res

        ans = dfs(0, -1)
        return -1 if ans == inf else ans

if __name__ == "__main__":
    sol = Solution()
    arr1, arr2 = [1,5,3,6,7], [1,3,2,4]
    print(sol.makeArrayIncreasing(arr1, arr2))

            
