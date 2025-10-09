from collections import defaultdict
from itertools import accumulate
from typing import List


# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        # 自行解答，滑动窗口 + 前缀和
        l = ans = 0        
        pres = list(accumulate(nums, initial=0))
        cnt = defaultdict(int)

        for r, v in enumerate(nums):
            cnt[v] += 1
            while cnt[v] > 1:
                cnt[nums[l]] -= 1
                l += 1
            ans = max(ans, pres[r+1]-pres[l])
        return ans
