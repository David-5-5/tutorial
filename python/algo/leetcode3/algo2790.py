from typing import List

class Solution:
    def maxIncreasingGroups(self, usageLimits: List[int]) -> int:

        ans = s = 0
        for v in sorted(usageLimits):
            s += v
            if s >= (ans + 2)*(ans+1) // 2:
                ans += 1
        return ans