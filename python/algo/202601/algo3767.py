from typing import List

# 一、贪心策略 - 1.1 从最小/最大开始贪心
class Solution:
    def maxPoints(self, technique1: List[int], technique2: List[int], k: int) -> int:
        # 自行解答
        ans = 0
        for i, [t1, t2] in enumerate(sorted(zip(technique1, technique2), key=lambda p:p[1]-p[0])):
            if i < k: ans += t1
            else: ans += max(t1, t2)
        return ans
