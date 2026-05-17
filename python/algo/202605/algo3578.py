from collections import deque
from typing import List

# 五、划分型 DP - 5.2 最优划分
class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:
        # translate from c++
        mod = 10 ** 9 + 7
        inc, asc = deque(), deque()
        dp = [0] * (len(nums) + 1)
        dp[0] = 1

        l, sum = 0, 0
        for i, x in enumerate(nums):
            sum += dp[i]
            while inc and nums[inc[-1]] < x: inc.pop()
            inc.append(i)

            while asc and nums[asc[-1]] > x: asc.pop()
            asc.append(i)

            while nums[inc[0]] - nums[asc[0]] > k:
                sum -= dp[l]
                l += 1
                if inc[0] < l: inc.popleft()
                if asc[0] < l: asc.popleft()
            sum %= mod
            dp[i+1] = sum
        return dp[-1]