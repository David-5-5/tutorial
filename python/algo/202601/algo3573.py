
from cmath import inf
from functools import cache
from typing import List

# 动态规划 - 六、状态机 DP 6.1 买卖股票
class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        # 参考题解
        n = len(prices)

        @cache
        def dfs(i: int, c:int, l:int) -> int:
            # if l < 0 : return -inf    
            if l == 0 : return 0    # l 有两种写法
            if i < 0: return -inf if c else 0

            p = prices[i]
            if c == 0:
                return max(dfs(i-1, 0, l), dfs(i-1, 1, l) + p, dfs(i-1, 2, l) - p)  # 普通交易 买入
            if c == 1:
                return max(dfs(i-1, 1, l), dfs(i-1, 0, l-1) - p) # 普通交易 买出
            return max(dfs(i-1, 2, l), dfs(i-1, 0, l-1) + p) # 做空交易 买入

            return res
        ans = dfs(n-1, 0, k)
        dfs.cache_clear()
        return ans