from collections import deque
from typing import List

# 双周赛 134
class Solution:
    def maximumPoints(self, enemyEnergies: List[int], currentEnergy: int) -> int:
        # 自行解答，模拟
        enemyEnergies.sort()
        ans = 0
        if currentEnergy < enemyEnergies[0]: return ans
        
        while enemyEnergies:
            while enemyEnergies[0] <= currentEnergy:
                val = currentEnergy // enemyEnergies[0]
                currentEnergy -= enemyEnergies[0] * val
                ans += val
            currentEnergy += enemyEnergies.pop()
        return ans

if __name__ == "__main__":
    sol = Solution()
    enemyEnergies, currentEnergy = [3,2,2], 2
    print(sol.maximumPoints(enemyEnergies, currentEnergy))