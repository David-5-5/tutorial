from sortedcontainers import SortedDict    
class SummaryRanges:

    def __init__(self):
        # The key is lower, value is upper
        self.cache = SortedDict()

    def addNum(self, value: int) -> None:
        # The inx is the pos to insert, Then
        # The key of (inx-1) is <= value, if exist
        # The key of inx is > value, if exist
        inx = self.cache.bisect_right(value)
        # I, key_(inx-1) <= value <= value_(inx-1)
        if inx and value <= self.cache.peekitem(inx-1)[1]:
            return
        # II, value_(inx-1) == value - 1 and value + 1 = key_(inx), merge inx-1 and inx
        elif inx and value - 1 == self.cache.peekitem(inx-1)[1] and inx < len(self.cache) and value + 1 == self.cache.peekitem(inx)[0]:
            item = self.cache.popitem(inx)
            self.cache[self.cache.peekitem(inx-1)[0]] = item[1]
        # III, value_(inx-1) == value - 1, update value of (inx-1)
        elif inx and value - 1 == self.cache.peekitem(inx-1)[1]:
            self.cache[self.cache.peekitem(inx-1)[0]] = value
        # IV, value + 1 = key_(inx), Remove original item of inx
        # add new key as value, value is original value_(inx)
        elif inx < len(self.cache) and value + 1 == self.cache.peekitem(inx)[0]:
            item = self.cache.popitem(inx)
            self.cache[value] = item[1]
        else:
            self.cache[value] = value

    def getIntervals(self):
        return [[i,j] for i,j in self.cache.items()]




# Your SummaryRanges object will be instantiated and called as such:
# obj = SummaryRanges()
# obj.addNum(value)
# param_2 = obj.getIntervals()