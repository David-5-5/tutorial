from bisect import bisect_left
from typing import List

# 一、贪心策略 - 1.4 从最左/最右开始贪心
class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        # 自行解答 最小最大值 二分答案 2748
        n = len(points)
        mx = max(points)

        def check(upper: int) -> int:
            prev, cnt = 0, 0

            for i, val in enumerate(points):
                if val * prev >= upper and i == n-1 or cnt > m: return cnt

                div = (upper + val -1) // val # ceilling
                prev = max(0, div - 1 - prev)
                cnt += 1 + 2 * prev
                # if : return cnt      # 剪枝
            return cnt
        
        l , r = 0, mx * m // n + 1
        while (l + 1 < r) :
            mid = (l + r) // 2
            if check(mid) <= m: l = mid
            else: r = mid
        
        return l