from collections import defaultdict
from typing import List

# 双周赛 84 自行解答
class Solution:
    def countBadPairs(self, nums: List[int]) -> int:
        cnt, n = defaultdict(int), len(nums)
        res = 0
        for i, v in enumerate(nums):
            res += cnt[v-i]
            cnt[v-i] += 1
        return n * (n-1)//2 - res
    
        # nums = [v - i for i, v in enumerate(nums)]
        # cnt = Counter(nums)
        # return n * (n-1) // 2 - sum(v*(v-1)//2 for v in cnt.values())

        # res = n * (n-1)//2
        # for i, v in enumerate(nums):
        #     res -= cnt[v-i]
        #     cnt[v-i] += 1
        # return  res