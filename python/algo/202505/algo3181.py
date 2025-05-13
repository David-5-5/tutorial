from typing import List

# 动态规划 - 11.9 其他优化 DP
class Solution:
    def maxTotalReward(self, rewardValues: List[int]) -> int:
        # 参考题解，位运算优化
        rewardValues.sort()
        if len(rewardValues) >= 2 and rewardValues[-2] == rewardValues[-1] - 1:
            return 2 * rewardValues[-1] - 1
        f = 1
        for x in rewardValues:
            f |= (f & ((1 << x) - 1)) << x
        return f.bit_length() - 1
        