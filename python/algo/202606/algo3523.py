from typing import List

# 贪心 八、其他
class Solution:
    def maximumPossibleSize(self, nums: List[int]) -> int:
        last, ans = nums[0], 1
        for v in nums[1:]:
            if v >= last:
                last = v
                ans += 1
        return ans