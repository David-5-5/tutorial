from math import gcd


class Solution:
    def isReachable(self, targetX: int, targetY: int) -> bool:
        g = gcd(targetX, targetY)
        if g & (g-1) == 0:
            return True
        else: return False