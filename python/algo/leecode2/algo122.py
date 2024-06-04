from typing import List
from functools import lru_cache
# 状态机DP
# dfs(i:int, hold:bool) 表示第 i 天是否股票的最大收益，
#                       hold=False 不持有股票
#                       hold=True  持有股票
# 第 i 天状态可以为 持有/不持有，其状态转移方程为
# dfs(i, False) = max(dfs(i-1, False),          不变化
#                 dfs(i-1, True) + prices[i])   卖掉股票
# dfs(i, True) = max(dfs(i-1, True),           不变化
#                dfs(i-2, False) - prices[i])   买入股票
# 最后一天当然不持有股票的利润最大，因此从
# 边界条件:
#   dfs(-1,False) = 0
#   dfs(-1,True) = - INF
# dfs(n-1, False) 开始递归
class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        @lru_cache(maxsize = None)
        def dfs(i:int, hold:bool):
            if i < 0:
                return -float("inf") if hold else 0
            if hold:
                return max(dfs(i-1,True),dfs(i-1, False)-prices[i])
            return max(dfs(i-1, False), dfs(i-1,True) + prices[i])

        return dfs(n-1,False)

if __name__ == "__main__":
    sol = Solution()
    prices = [7,1,5,3,6,4]
    print(sol.maxProfit(prices))