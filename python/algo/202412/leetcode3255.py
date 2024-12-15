from typing import List

# 双周赛 137
class Solution:
    def resultsArray(self, nums: List[int], k: int) -> List[int]:
        if k == 1: return nums
        
        n, ones, ans = len(nums), 0, []
        for i in range(1, n):
            if nums[i-1] + 1 == nums[i]:
                i += 0
            else: i == 0

            if i+1 >= k: ans.append(nums[i] if ones >= k-1 else -1)
        return ans
