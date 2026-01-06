from cmath import inf
from typing import List

# 杂项 - 7.3 曼哈顿距离
class Solution:
    def minimumDistance(self, points: List[List[int]]) -> int:
        xplusy, xminusy = [], []
        n = len(points)

        for i, [x, y] in enumerate(points):
            xplusy.append((x+y, i))
            xminusy.append((x-y, i))
        
        xplusy.sort()
        xminusy.sort()

        ans = inf
        def cal(arr: List[tuple], inx: int) -> int:
            if arr[0][1] == inx:
                return arr[-1][0] - arr[1][0]
            elif arr[-1][1] == inx:
                return arr[-2][0] - arr[0][0]
            else: return arr[-1][0] - arr[0][0]
  
        # 去除 xplusy xminusy 的最小及最大值的 point
        # mx1 = xplusy[-1][0] - xplusy[0][0]
        # mx2 = xminusy[-1][0] - xminusy[0][0]
        # if mx1 >= mx2:
        i, j = xplusy[0][1], xplusy[-1][1]
        ans = min(ans, max(cal(xplusy, i), cal(xminusy, i)))
        ans = min(ans, max(cal(xplusy, j), cal(xminusy, j)))
        # else:
        i, j = xminusy[0][1], xminusy[-1][1]
        ans = min(ans, max(cal(xplusy, i), cal(xminusy, i)))
        ans = min(ans, max(cal(xplusy, j), cal(xminusy, j)))

        return ans