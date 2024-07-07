from bisect import bisect_left
from itertools import pairwise
from typing import List

class Solution:
    def minimizeMax(self, nums: List[int], p: int) -> int:
        nums.sort()

        def check(mx:int) -> bool:
            cnt = i = 0
            
            while i < len(nums) - 1:
                if nums[i+1] - nums[i] <= mx:
                    cnt += 1
                    i += 2
                else:
                    i += 1
            return cnt

        # return bisect_left(range(nums[-1]-nums[0]), p, key=check)
        left = -1
        right = nums[-1] - nums[0] + 1
        while left + 1 < right:
            mid = (left + right) // 2
            if check(mid) < p:
                left = mid
            else:
                right = mid
        return right
    
if __name__ == "__main__":
    sol = Solution()
    nums, p = [3,4,2,3,2,1,2], 3
    print(sol.minimizeMax(nums, p))