from bisect import bisect_left
from collections import defaultdict
from typing import List

# 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution:
    def medianOfUniquenessArray(self, nums: List[int]) -> int:
        n = len(nums)
        k = (((n + 1) * n // 2) + 1) // 2 # ceil((n*(n+1)/2)/2)

        # upper 说明 upper 大于期望值，缩小
        def check(upper : int) -> int:
            freq = defaultdict(int)
            l = cnt = 0
            for r, v in enumerate(nums):
                freq[v] += 1
                while len(freq) > upper:
                    freq[nums[l]] -= 1
                    if (freq[nums[l]]) == 0: del freq[nums[l]]
                    l += 1
                cnt += r - l  + 1
                if cnt >= k:return True
            return False
        
        return bisect_left(range(len(set(nums))), True, 1, key=check)