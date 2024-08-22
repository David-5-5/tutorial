from typing import List


class Solution:
    def countDistinctIntegers(self, nums: List[int]) -> int:
        # return len(set(nums) | set([int(str(c)[::-1])for c in nums]))
        s = set()
        for c in nums:
            s.add(c)
            x = 0
            while c:
                x = x*10 + c % 10
                c // 10
            s.add(x)
        return len(s)