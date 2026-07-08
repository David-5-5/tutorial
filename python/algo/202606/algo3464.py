from bisect import bisect_left
from typing import List

# 复习
class Solution:
    def maxDistance(self, side: int, points: List[List[int]], k: int) -> int:
        # 二分答案 + 二分查找
        arr = []
        for p in points:
            x, y = p[0], p[1]
            if x == 0: arr.append(y)
            elif y == side: arr.append(side + x)
            elif x == side: arr.append(3 * side - y)
            elif y == 0: arr.append(4 * side - x)
        
        arr.sort()

        def check(limit: int) -> bool:
            for x in arr:
                end = x + 4 * side - limit
                for _ in range(k-1):
                    inx = bisect_left(arr, x + limit)
                    if inx == len(arr) or arr[inx] > end:
                        break
                    x = arr[inx]
                else: return True
            return False

        l, r = 1, side * 4 // k + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid): l = mid
            else: r = mid
        return l

