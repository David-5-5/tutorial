from typing import List

# 贪心专题 单序列配对
class Solution:
    def maximizeGreatness(self, nums: List[int]) -> int:
        # 自行解答 
        n = len(nums)
        ans = l = r = 0
        nums.sort()
        while r < n:
            if nums[l] < nums[r]:
                l += 1
                r += 1
                ans += 1
            else:
                r += 1
        return ans