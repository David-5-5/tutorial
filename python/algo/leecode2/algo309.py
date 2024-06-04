from typing import List
from functools import lru_cache
# 状态机DP
# 基本思路参加 algo 122
# 由于 卖出股票后第二天不能买入股票，因此状态转移方程更改
# dfs(i, True) = max(dfs(i-1, True),           不变化
#                dfs(i-2, False) - prices[i])   买入股票
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        @lru_cache(maxsize = None)
        def dfs(i:int, hold:bool):
            if i < 0:
                return -float("inf") if hold else 0
            if hold:
                return max(dfs(i-1,True),dfs(i-2, False)-prices[i])
            return max(dfs(i-1, False), dfs(i-1,True) + prices[i])

        return dfs(n-1,False)

if __name__ == "__main__":
    sol = Solution()
    prices = [7,1,5,3,6,4]
    print(sol.maxProfit(prices))