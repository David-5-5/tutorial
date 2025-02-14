from typing import List


class Solution:
    def change(self, amount: int, coins: List[int]) -> int:
        # 自行解答 完全背包 
        dp = [0] * (amount + 1)
        dp[0] = 1
        for c in coins:
            for k in range(c, amount+1):
                dp[k] += dp[k-c]
        return dp[-1]