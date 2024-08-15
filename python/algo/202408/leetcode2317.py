from functools import reduce
from operator import or_
from typing import List


class Solution:
    def maximumXOR(self, nums: List[int]) -> int:
        return reduce(or_, nums)


if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,4,6]
    print(sol.maximumXOR(nums))