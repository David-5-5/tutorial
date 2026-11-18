from collections import defaultdict
from typing import List


class Solution:
    def maxSubarray(self, nums: List[int]) -> int:
        seen = defaultdict(int)
        def check(cur: int) -> bool:
            for k in seen:
                if cur + k in seen:
                    return False
                if cur > k:
                    if cur - k == k :   # Edge cases: cur - k == k
                        if seen[k] > 1: return False
                    elif cur - k in seen: return False
                if k > cur:
                    if k - cur in seen: return False
            return True
        
        # Sliding windows
        l, ans = 0, 0
        for r, v in enumerate(nums):
            while not check(v):
                seen[nums[l]] -= 1
                if seen[nums[l]] == 0:
                    del seen[nums[l]]
                l += 1
            seen[v] += 1
            ans = max(ans, r - l + 1)
        return ans
    