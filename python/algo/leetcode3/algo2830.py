from typing import List

# 力扣周赛 359, 属于[线性 DP] 不相交区间
# refer to https://www.bilibili.com/video/BV1Xj411K7oF/
# https://leetcode.cn/problems/maximize-the-profit-as-the-salesman/solutions/2396402/xian-xing-dpfu-xiang-si-ti-mu-pythonjava-wmh7/
# https://leetcode.cn/circle/discuss/tXLS3i/
class Solution:
    def maximizeTheProfit(self, n: int, offers: List[List[int]]) -> int:
        # 2024.12 复习
        # 贪心不相交区间 和 DP不相交区间的差异点：
        # 1, 贪心会按照左、右端点排序，DP 分组 (必须还是可选？)
        # 2, ...

        # 本题的状态转移方程 dp[i] = max(dp[i],dp[k_s]+k_g)
        #   其中 k_s 是 第 k 个买家购买的房屋起始序号，i = end_k + 1，k_s = start_k,
        #       k_g是第 k 个买家的金币数
        group = [[] for _ in range(n)] # 按照end 分组

        for st, end, gold in offers:
            group[end].append((st, gold))

        dp = [0] * (n+1)
        for end, grp in enumerate(group): # 每个房间
            dp[end+1] = dp[end]
            for st, g in grp: # grp 可能为空
                dp[end+1] = max(dp[end+1], dp[st] + g)
                
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    n, offers = 10, [[0,0,1],[4,6,2]]
    print(sol.maximizeTheProfit(n, offers))    