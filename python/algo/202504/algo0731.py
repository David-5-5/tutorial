from bisect import bisect_left


class MyCalendarTwo:

    def __init__(self):
        self.booked = []
        self.overlaps = []
        

    def book(self, startTime: int, endTime: int) -> bool:
        # 从图形上 当 endTime <= s or e <= startTime 时， 无交集，其求反，即有交集
        if any(s < endTime and startTime < e for s, e in self.overlaps):
            return False

        for s, e in self.booked:
            if s < endTime and startTime < e:
                self.overlaps.append(max(s, startTime), min(e, endTime))

        self.booked.append(startTime, endTime)


# Your MyCalendarTwo object will be instantiated and called as such:
# obj = MyCalendarTwo()
# param_1 = obj.book(startTime,endTime)