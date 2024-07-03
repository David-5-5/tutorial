from itertools import pairwise
from typing import List

class Solution:
    def checkArray(self, nums: List[int], k: int) -> bool:
        n = len(nums)
        diff = [0] * n
        diff[0] = nums[0]

        for i, (n0,n1) in enumerate(pairwise(nums)):
            diff[i+1] = n1 - n0
        
        for i, d in enumerate(diff):
            if d < 0 or (d > 0 and i + k > n):
                return False
            if d == 0:
                continue
            diff[i] -= d
            if i + k < n:
                diff[i+k] += d
        return True


if __name__ == "__main__":
    sol = Solution()
    print(sol.checkArray([0,45,82,98,99], 4))