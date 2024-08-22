from typing import List


class Solution:
    def countDistinctIntegers(self, nums: List[int]) -> int:
        return len(set(nums) | set([int(str(c)[::-1])for c in nums]))