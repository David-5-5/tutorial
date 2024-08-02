from functools import reduce
from operator import xor
from typing import List


class Solution:
    def xorAllNums(self, nums1: List[int], nums2: List[int]) -> int:
        return (reduce(xor, nums1) if len(nums2)%2 == 1 else 0) ^ (reduce(xor, nums2) if len(nums1)%2 == 1 else 0)


if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [2,1,3], [10,2,5,0]
    print(sol.xorAllNums(nums1, nums2))