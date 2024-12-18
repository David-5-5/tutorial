from bisect import bisect_right
from typing import List

# 贪心专题 - 合并区间
class Solution:
    def insert(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        # 分类讨论
        ans = []
        left, right = newInterval
        if not intervals: return [newInterval]
        for i, (l, r) in enumerate(intervals):
            if right < l:
                ans.append([left,right])
                ans.extend(intervals[i:])
                return ans
            elif right == l:
                ans.append([left, r])
                ans.extend(intervals[i+1:])
                return ans
            elif left > r:
                ans.append([l,r])
            elif left == r:
                left = l
            elif l <= left and right <= r:
                ans.extend(intervals[i:])
                return ans
            else:
                left = min(l, left)
                right = max(right, r)
        ans.append([left, right])
        return ans

    def insert2(self, intervals: List[List[int]], newInterval: List[int]) -> List[List[int]]:
        # 参考 0056 代码清晰，可读性强
        ans = []
        
        inx = bisect_right(intervals, newInterval)
        intervals.insert(inx, newInterval)

        left, right = intervals[0]
        for l, r in intervals[1:]:
            if l > right:
                ans.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        ans.append([left, right])

        return ans

