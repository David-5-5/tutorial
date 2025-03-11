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

    def longestArithSeqLength2(self, nums: List[int]) -> int:
        ans = 2
        mx, mn = max(nums), min(nums)

        for d in range((mn-mx)//2, (mx-mn)//2+1):  # 枚举方差
            dp = [0] * (mx + 1)
            for x in nums:  # 数组代替map，时间复杂度一样，性能极大提升
                dp[x] = dp[x-d] + 1 if 0 <= x - d <= mx else 1
                if dp[x] > ans: ans = dp[x]
        
        return ans