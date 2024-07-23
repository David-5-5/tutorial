from functools import reduce
from operator import xor
from typing import List


class Solution:
    def xorBeauty(self, nums: List[int]) -> int:
        return reduce(xor, nums)
    
if __name__ == "__main__":
    nums = [15,45,20,2,34,35,5,44,32,30]
    solution = Solution()
    print(solution.xorBeauty(nums))