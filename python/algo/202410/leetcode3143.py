from collections import defaultdict
from math import inf
from typing import List

# 双周赛 130
class Solution:
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:
        # 自行解答，枚举
        pd = defaultdict(lambda:inf) # 每类标签的最小半径
        mx = inf # 存储出现重复标签的最小值，包含的类型的最小半径必须小于 mx
        for i, (x, y) in enumerate(points):
            edge = 2 * max(abs(x),abs(y))
            if pd[s[i]] > edge:
                mx = min(mx, pd[s[i]])
                pd[s[i]] = edge
            else:
                mx = min(mx, edge)
            if mx == 0: return 0 # 剪枝

        ans = 0
        for k in pd.keys():
            if pd[k] < mx: ans += 1
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    points, s = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], "abdca"
    print(sol.maxPointsInsideSquare(points, s))
