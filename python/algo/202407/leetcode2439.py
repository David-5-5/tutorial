from bisect import bisect_left
from typing import List

class Solution:
    def minimizeArrayValue(self, nums: List[int]) -> int:

        def check(limit: int) -> bool:
            inc = 0
            for v in reversed(nums):
                if inc + v > limit:
                    inc = inc + v - limit
                else:
                    inc = 0
            if inc > 0: return False
            return True

        return bisect_left(range(max(nums) + 1), True, key = check)
   
if __name__ == "__main__":
    sol = Solution()
    nums = [3,7,1,6]
    print(sol.minimizeArrayValue(nums))