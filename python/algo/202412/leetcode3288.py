from bisect import bisect_left
from typing import List

# 双周赛
class Solution:
    def maxPathLength(self, coordinates: List[List[int]], k: int) -> int:
        # 参考题解，最长子序列
        kx, ky = coordinates[k]
        # 相同的 xi, yi1, yi2, yi3, ... yi1 > yi2 > yi3 ...
        # 仅保留 min(yi1,yi2,yi3....) > yi-1,j
        coordinates.sort(key = lambda p:(p[0],-p[1]))
        dp = []

        for x, y  in coordinates:
            if (x < kx and y < ky)  or (x > kx and y > ky):
                inx = bisect_left(dp, y)
                if (inx) < len(dp):
                    dp[inx] = min(dp[inx], y)
                else:
                    dp.append(y)

        return len(dp) + 1