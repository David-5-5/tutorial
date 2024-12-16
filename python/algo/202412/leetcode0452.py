from typing import List

# 贪心专题 区间选点
class Solution:
    def findMinArrowShots(self, points: List[List[int]]) -> int:
        # 自行解答
        ans, right = 0, - 2**31 - 1 # 最后满足要求的right
        points.sort(key=lambda p:p[1]) # 按照右端点排序
        for l, r in points:
            # 由于按照右端点排序，因此 right <= r
            if l <= right: continue # 满足 l <= right <= r
            else:
                ans += 1  # 需要射出新的箭
                right = r # 设置为当前的节点的右端点
        return ans