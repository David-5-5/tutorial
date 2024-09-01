from bisect import bisect_right
from cmath import inf
from typing import List

# 周赛 310
class Solution:
    def minGroups(self, intervals: List[List[int]]) -> int:
        intervals.sort()
        
        ans = right = 0
        while intervals:
            inx = bisect_right(intervals, [right,inf])
            if inx == len(intervals):
                ans += 1
                right = 0
            else:
                _, right = intervals.pop(inx)
        return ans + 1


if __name__ == "__main__":
    sol = Solution()
    intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
    print(sol.minGroups(intervals))