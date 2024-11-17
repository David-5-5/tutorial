from math import inf
from typing import List


class Solution:
    def minDifference(self, nums: List[int]) -> int:
        mn, mx = inf, -inf
        for v in nums:
            if v == -1:continue
            if v < mn: mn = v
            if v > mx: mx = v
        if mx <= mn: return 0

        # def check()
        
    
if __name__ == "__main__":
    sol = Solution()
    print(sol)