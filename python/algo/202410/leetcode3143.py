from collections import defaultdict
from math import inf
from typing import List

# 双周赛 130
class Solution:
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:
        # 自行解答，枚举
        pd = defaultdict(lambda:inf)
        mx = inf
        for i, (x, y) in enumerate(points):
            edge = 2 * max(abs(x),abs(y))
            if pd[s[i]] > edge:
                mx = min(mx, pd[s[i]])
                pd[s[i]] = edge
            else:
                mx = min(mx, edge)

        ans = 0
        for k in pd.keys():
            if pd[k] < mx: ans += 1
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    points, s = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], "abdca"
    print(sol.maxPointsInsideSquare(points, s))
