from math import atan2, degrees
from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def visiblePoints(self, points: List[List[int]], angle: int, location: List[int]) -> int:
        # 计算极角的度数, 浮点数 [0,360)
        def cal_degree(x:int, y:int) -> float:
            rad = atan2(y, x)
            deg = degrees(rad)
            if deg < 0:
                deg += 360
            return deg  # 结果为0°到359.999...°
    
        x0, y0 = location
        deg_list, locs = [], 0
        for x, y in points:
            if x == x0 and y == y0: locs += 1   # 极点一定包含
            else:deg_list.append(cal_degree(x-x0,y-y0))
        deg_list.sort()
        deg_list += [x+360 for x in deg_list] # 循环列表

        m = len(points)
        l = ans = 0
        for r, d in enumerate(deg_list):
            while deg_list[l] + angle < d:
                l += 1
            ans = max(ans, r-l+1)
            if (ans + locs) == m:return m
        return ans + locs