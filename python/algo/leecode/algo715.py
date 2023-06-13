from sortedcontainers import SortedDict
class RangeModule:

    def __init__(self):
        # The dict of interval, the key is left of interval, and the value is right of interval
        self.intes = SortedDict()

    def addRange(self, left: int, right: int) -> None:
        intes = self.intes

        inx = intes.bisect_right(left)
        if inx != 0:
            start = inx - 1
            if intes.values()[start] >= right:
                return
            if intes.values()[start] < right and intes.values()[start] >= left:
                left = intes.keys()[start]
                intes.popitem(start)
                inx -= 1
        
        while inx < len(intes) and intes.keys()[inx] <= right:
            right = max(right, intes.values()[inx])
            intes.popitem(inx)
        
        intes[left] = right
 

    def queryRange(self, left: int, right: int) -> bool:
        intes = self.intes

        inx = intes.bisect_right(left)

        if inx != 0:
            if intes.keys()[inx - 1] <= left and intes.values()[inx - 1] >= right:
                return True

        return False

    def removeRange(self, left: int, right: int) -> None:
        intes = self.intes
        inx = intes.bisect_right(left)
        if inx != 0:
            start = inx - 1
            if intes.values()[start] >= left and intes.values()[start] <= right:
                intes[intes.keys()[start]] = left
            elif intes.values()[start] > right:
                intes[right] = intes.values()[start]
                intes[intes.keys()[start]] = left
                return
            if intes.keys()[start] == left and intes.values()[start] <= right:
                intes.popitem(start)
                inx -= 1

        while inx < len(intes) and intes.values()[inx] <= right:
            intes.popitem(inx)
        
        if inx < len(intes) and right > intes.keys()[inx] :
            r1 = intes.values()[inx]
            intes.popitem(inx)
            intes[right] = r1

# Your RangeModule object will be instantiated and called as such:
obj = RangeModule()

# test case 
# obj.addRange(10,20)
# obj.removeRange(14,16)
# print(obj.queryRange(16,17))

# No.8 test case 
# obj.addRange(5,8)
# print(obj.queryRange(3,4))
# obj.removeRange(5,6)
# obj.removeRange(3,6)
# obj.addRange(1,3)
# print(obj.queryRange(2,3))
# obj.addRange(4,8)
# print(obj.queryRange(2,3))
# obj.removeRange(4,9)

# 
obj.addRange(44,53)
obj.addRange(69,89)
obj.removeRange(86,91)
obj.addRange(87,94)
obj.removeRange(34,52)
obj.addRange(1,59)
obj.removeRange(62,96)
obj.removeRange(34,83)
print(obj.queryRange(11,59))

