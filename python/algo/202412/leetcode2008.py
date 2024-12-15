from typing import List

# DP专题 - 不相交区间； 与贪心不相交区间对比练习
class Solution:
    def maxTaxiEarnings(self, n: int, rides: List[List[int]]) -> int:
        # 参考 2830 区间按照右端点进行分组
        # 2830 和 2008 差别在于 端点的包含关系不同
        # 2830 [0,1][1,2] 编号为房子单元，因此 1 两个区间内，因此区间重叠
        # 2830 [0,1][1,2] 编号为起始的点，因此是两个区间的交界点，区间不重叠
        
        group = [[] for _ in range(n)] # 按照end 分组

        for st, end, tip in rides:
            group[end-1].append((st-1, tip))

        dp = [0] * n
        for end, grp in enumerate(group): # 
            dp[end] = dp[end-1] if end > 0 else 0
            for st, t in grp: # grp 可能为空
                dp[end] = max(dp[end], dp[st] + end - st + t)
                
        return dp[n-1]