from typing import List

# 动态规划 - 0-1 背包
class Solution:
    def maxTotalReward(self, rewardValues: List[int]) -> int:
        # 自行解答
        rewardValues.sort()
        rewards = set()

        for v in rewardValues:
            new = set()
            new.add(v)
            for re in sorted(rewards):
                if re >= v: break
                new.add(re + v)
            rewards |= new
        return max(rewards)

        