from typing import List

# 
class Solution:
    def maxPossibleScore(self, start: List[int], d: int) -> int:
        start.sort()
        n = len(start)

        def check(l: int) -> bool:
            pos = 0
            for v in start:
                if pos > v + d: return False
                pos = max(pos, v) + l
            return True

        l, r = 0, start[n-1] + d + 1
        while l + 1 < r:
            m = (l + r) // 2
            if check(m): l = m
            else: r = m
        return l
        


