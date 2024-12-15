from bisect import bisect_right
from typing import List

# DP专题 - 不相交区间； 与贪心不相交区间对比练习
class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        # 二维 DP
        # 基于 1235,增加一位用于统计参会次数
        n = len(events)
        dp = [[0] * (k+1) for _ in range(n+1)] # 增加一维

        events.sort(key=lambda p:p[1]) # 按照 end 排序
        end = [r for _, r, _ in events]
        
        for i, (l, _, v) in enumerate(events):
            prev = bisect_right(end, l-1)
            for j in range(k):  # 二重循环 k * n <= 10 ^ 6
                dp[i+1][j+1] = max(dp[i][j+1], dp[prev][j] + v)

        return dp[n][k]