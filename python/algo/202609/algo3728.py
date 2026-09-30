from collections import defaultdict
from typing import List


class Solution:
    def countStableSubarrays(self, capacity: List[int]) -> int:
        cnt, n, pres, ans = defaultdict(int), len(capacity), 0, 0

        for i in range(n):
            ans += cnt[(capacity[i], pres-capacity[i])]
            if i: cnt[(capacity[i-1], pres)] += 1
            pres += capacity[i]
        
        return ans