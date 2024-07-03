import math
from typing import List


class Solution:
    def minimumReplacement(self, nums: List[int]) -> int:
        ans = 0

        limit = nums[-1]
        for v in reversed(nums):
            x = math.ceil(v/limit)
            ans += x - 1
            limit = math.floor(v/x)
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums = [3,9,3]
    print(sol.minimumReplacement(nums))