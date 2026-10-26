class Solution:
    def minimumTime(self, time: list[int], totalTrips: int) -> int:
        l, r = 0, totalTrips * max(time) + 1
        
        def check(limit: int) -> bool:
            res = 0
            for t in time:
                res += limit // t

            return res >= totalTrips

        while l + 1 < r:
            m = (l + r) // 2
            if check(m): r = m
            else: l = m
        
        return r