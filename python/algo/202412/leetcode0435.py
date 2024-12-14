from typing import List

# 贪心专题 - 不相交区间
class Solution:
    def eraseOverlapIntervals(self, intervals: List[List[int]]) -> int:
        # 自行解答
        # 按左端点从大到小排序，从后往前选择区间，
        # 左端点尽量大，这样最大程度大于前一个区间的右端点
        intervals.sort(reverse= True) 

        left = intervals[0][0]
        ans = 0
        for l, r in intervals[1:]:
            if r > left: ans += 1 # 删除区间
            else: left = l        # 选择区间，并更新左端点的值
        return ans

        intervals.sort(key=lambda p:p[1]) # 按右端点排序
        # 因为右端点尽量小，才能有 后续的pair 的左端点 > 当前的右端点

    def eraseOverlapIntervals2(self, intervals: List[List[int]]) -> int:
        # 同 646
        right = intervals[0][1]
        ans = 1
        for l, r in intervals[1:]:
            if l >= right: # > 改为 >=
                ans += 1   # 保留的数
                right = r
        return len(intervals) - ans # 删除的数