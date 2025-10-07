from bisect import bisect_right
from cmath import inf
from itertools import accumulate
from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def minOperations(self, nums: List[int], x: int) -> int:
        # 自行解答，前缀和
        if sum(nums) < x: return -1
        pres = list(accumulate(nums, initial=0))
        n = len(nums)

        ans, suf_sum = inf, 0
        def check(left: int, suf: int):
            nonlocal ans
            p = bisect_right(pres, left)
            if p > 0 and pres[p-1] == left: 
                ans = min(ans, p-1+suf)
        
        check(x, 0)
        for i in range(n-1, -1, -1):
            suf_sum += nums[i]
            if x - suf_sum >= 0:
                check(x-suf_sum, n - i)
            else: break
        return -1 if ans == inf else ans

    def minOperations2(self, nums: List[int], x: int) -> int:
        # 逆向思维，移除和等于 sum(nums) - x 的最长子数组
        y = sum(nums) - x
        if y < 0:return -1
        pres = 0
        l, ans = 0, -1
        for r, v in enumerate(nums):
            pres += v
            while pres > y:
                pres -= nums[l]
                l += 1
            if pres == y: ans = max(ans, r - l + 1)
        
        return ans if ans == -1 else len(nums) - ans