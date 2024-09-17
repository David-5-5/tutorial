from itertools import pairwise
from typing import List

# 双周赛 122
class Solution:
    def canSortArray(self, nums: List[int]) -> bool:
        # 参考题解，分组循环
        n, i = len(nums), 0
        while i < n:
            start = i
            ones = nums[start].bit_count()
            i += 1
            while i < n and nums[i].bit_count() == ones:
                i += 1
            nums[start:i] = sorted(nums[start:i])
        
        return all(x <= y for x, y in pairwise(nums))
    

if __name__ == "__main__":
    sol = Solution()
    nums = [8,4,2,30,15]
    print(sol.canSortArray(nums))