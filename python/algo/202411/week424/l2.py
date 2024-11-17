from itertools import accumulate
from typing import List


class Solution:
    def isZeroArray(self, nums: List[int], queries: List[List[int]]) -> bool:
        n = len(nums)
        diff = [0] * n
        for l, r in queries:
            diff[l] += 1
            if r + 1 < n: diff[r+1] -= 1
        pres = list(accumulate(diff))

        return all(ori<=qu for ori, qu in zip(nums, pres))

    
if __name__ == "__main__":
    sol = Solution()
    nums, queries = [4,3,2,1], [[1,3],[0,2]]
    print(sol.isZeroArray(nums, queries))