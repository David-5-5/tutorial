from bisect import bisect_right
from typing import List

# 双周赛 128
class Solution:
    def minRectanglesToCoverPoints(self, points: List[List[int]], w: int) -> int:
        x_point = list(set([x for x, _ in points]))
        x_point.sort()
        
        if w == 0: return len(x_point)

        ans, inx = 1, 0

        inx = bisect_right(x_point, x_point[inx]+w)
        while inx < len(x_point):
            ans += 1
            inx = bisect_right(x_point, x_point[inx]+w)

        return ans
    
if __name__ == "__main__":
    sol = Solution()
    points, w  = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], 1
    points, w  = [[1,3],[8,8]], 1
    print(sol.minRectanglesToCoverPoints(points, w))