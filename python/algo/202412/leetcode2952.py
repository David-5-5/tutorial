from typing import List

# 周赛 374 
# 同 330
# 贪心专题 - 归纳法
class Solution:
    def minimumAddedCoins(self, coins: List[int], target: int) -> int:
        # [0, x-1] 在数组中 x 不在数组中，初始 x = 1, 即数组为空
        coins.sort()
        ans, x, l, n = 0, 1, 0, len(coins)

        while x <= target: # x-1 在数组中，x 不在数组中
            if l < n and coins[l] <= x:
                x += coins[l]
                l += 1
            else:
                ans += 1
                x <<= 1
        return ans