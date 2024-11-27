from collections import defaultdict
from typing import List

# 贪心专题
class Solution:
    def maxNonOverlapping(self, nums: List[int], target: int) -> int:
        pre_sum = defaultdict(int)

        ans = 0
        for v in nums:
            if v == target or pre_sum[target-v]:
                pre_sum.clear()
                ans += 1
            else:
                tmp = defaultdict(int)
                for k in pre_sum.keys():
                    tmp[k+v] = 1
                tmp[v] = 1
                pre_sum = tmp
        return ans



                