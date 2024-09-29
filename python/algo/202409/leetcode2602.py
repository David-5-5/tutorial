from bisect import bisect_left
from itertools import accumulate
from typing import List


class Solution:
    def minOperations(self, nums: List[int], queries: List[int]) -> List[int]:
        nums.sort()
        n, m = len(nums), len(queries)
        pres = list(accumulate(nums, initial= 0))

        ans = [0] * m
        for i, q in enumerate(queries):
            inx = bisect_left(nums, q)
            ans[i] += inx * q - (pres[inx] - pres[0])
            ans[i] += (pres[-1] - pres[inx]) - (n-inx) * q

        return ans

if __name__ == "__main__":
    sol = Solution()    
    nums, queries = [3,1,6,8], [1,5,9]
    print(sol.minOperations(nums,queries))