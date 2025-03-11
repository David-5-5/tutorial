from collections import defaultdict
from typing import List

# 动态规划 - 合法子序列 DP
class Solution:
    def longestArithSeqLength(self, nums: List[int]) -> int:
        # 自行解答， 3688ms 刚刚通过
        dp = defaultdict(int)
        ans = 2 # 至少为 2
        mx, mn = max(nums), min(nums)

        for x in nums:
            for d in range((mn-mx)//2, (mx-mn)//2+1):  # mx - mn 差的一半
                dp[(d, x)] = dp[(d, x-d)] + 1
                if dp[(d,x)] > ans: ans = dp[(d,x)]
        
        return ans