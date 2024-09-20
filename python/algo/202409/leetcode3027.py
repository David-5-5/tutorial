from cmath import inf
from typing import List

# 双周赛 123
class Solution:
    def numberOfPairs(self, points: List[List[int]]) -> int:
        points.sort(key = lambda p:(p[0],-p[1]))
        ans = 0
        for i, (_, y0) in enumerate(points):
            max_y = -inf
            for _, y1 in points[i+1:]:
                if max_y < y1 <= y0:
                    max_y = y1
                    ans += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    points = [[1,1],[2,2],[3,3]]
    points = [[1,2],[2,1],[3,0]]
    print(sol.numberOfPairs(points))