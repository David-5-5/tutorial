from typing import List
# 力扣周赛 359, 属于[线性 DP]
# refer to https://www.bilibili.com/video/BV1Xj411K7oF/
# https://leetcode.cn/problems/maximize-the-profit-as-the-salesman/solutions/2396402/xian-xing-dpfu-xiang-si-ti-mu-pythonjava-wmh7/
# https://leetcode.cn/circle/discuss/tXLS3i/
class Solution:
    def maximizeTheProfit(self, n: int, offers: List[List[int]]) -> int:
        group = [[] for _ in range(n)]

        for st, end, gold in offers:
            group[end].append((st, gold))

        dp = [0] * (n+1)
        for end, grp in enumerate(group):
            dp[end+1] = dp[end]
            for st, g in grp:
                dp[end+1] = max(dp[end+1], dp[st] + g)
                
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    n, offers = 5, [[0,0,1],[0,2,2],[1,3,2]]
    print(sol.maximizeTheProfit(n, offers))    