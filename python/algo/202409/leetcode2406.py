from bisect import bisect_right
from cmath import inf
import heapq
from typing import List

# 周赛 310
class Solution:
    def minGroups(self, intervals: List[List[int]]) -> int:
        # 自行解答
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

    def minGroups2(self, intervals: List[List[int]]) -> int:
        # 参考题解，使用堆
        intervals.sort()

        q = []
        for l, r in intervals:
            if q and l > q[0] :
                heapq.heapreplace(q, r) # 更改组
            else:
                heapq.heappush(q, r) # 增加新的组
        return len(q)

if __name__ == "__main__":
    sol = Solution()
    intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
    # print(sol.minGroups(intervals))
    print(sol.minGroups2(intervals))