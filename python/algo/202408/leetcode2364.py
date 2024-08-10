from collections import defaultdict
from typing import List


class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        cnt, n = defaultdict(int), len(nums)
        res = 0
        for i, v in enumerate(nums):
            res += cnt[v-i]
            cnt[v-i] += 1
        return n * (n-1)//2 - res
    
        # res = n * (n-1)//2
        # for i, v in enumerate(nums):
        #     res -= cnt[v-i]
        #     cnt[v-i] += 1
        # return  res