# 周赛 362
class Solution:
    def isReachableAtTime(self, sx: int, sy: int, fx: int, fy: int, t: int) -> bool:
        if t == 1:
            return (fx, fy) in [(sx-1,sy-1), (sx-1, sy), (sx-1, sy+1),(sx,sy-1), (sx, sy+1), (sx+1,sy-1), (sx+1, sy), (sx+1, sy+1)]

        return abs(fy-sy) <= t and abs(fx-sx) <= t