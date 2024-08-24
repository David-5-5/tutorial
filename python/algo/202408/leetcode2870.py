from collections import Counter
from typing import List

# 双周赛 114
class Solution:
    # 自行解答
    def minOperations(self, nums: List[int]) -> int:
        cnt = Counter(nums)
        ans = 0
        for v in cnt.values():
            if v == 1: return -1
            ans += v // 3
            if v % 3: ans += 1
        return ans
