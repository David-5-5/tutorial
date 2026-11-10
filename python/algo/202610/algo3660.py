from bisect import bisect_left, bisect_right
from itertools import accumulate
from math import inf
from typing import List

class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        n = len(nums)
        pre_mx = list(accumulate(nums, max))

        ans = [0] * n
        suf_min = inf
        for i in range(n-1, -1, -1):
            ans[i] = pre_mx[i] if pre_mx[i] <= suf_min else ans[i+1]
            suf_min = min(suf_min, nums[i])
        return ans

if __name__ == "__main__":
    print(Solution().maxValue([30,21,5,35,24]))
