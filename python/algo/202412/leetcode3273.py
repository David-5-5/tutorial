from typing import List

# 双周赛 138
class Solution:
    def minDamage(self, power: int, damage: List[int], health: List[int]) -> int:
        # 自行解答，贪心 按照 damage / second to kill enemy 从大到小排序

        # The time of second to kill enemy
        kill = [(h+power-1) // power for h in health ]
        
        ans, d_sum = 0, sum(damage)
        for dam, k in sorted(zip(damage, kill), key=lambda p:-p[0]/p[1]):
            ans += k * d_sum
            d_sum -= dam
        return ans