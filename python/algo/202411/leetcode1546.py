from collections import defaultdict
from typing import List

# 贪心专题
class Solution:
    def maxNonOverlapping(self, nums: List[int], target: int) -> int:
        # 自行解答
        pre_sum = defaultdict(int)
        pre_sum[0] = 1
        pres = 0
        
        ans = 0
        for v in nums:
            pres += v
            if pre_sum[pres-target]:
                pre_sum.clear()
                pre_sum[0] = 1
                pres = 0

                ans += 1
            else:
                pre_sum[pres] += 1
        return ans



                