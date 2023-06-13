import heapq

class Node:
    def __init__(self, val, prev=None, next=None):
        self.val = val
        self.prev = prev
        self.next = next

# direct linked node for insert
def insertBefore(insert:Node, before:Node):
    insert.prev = before.prev
    before.prev = insert
    insert.next = before
    if insert.prev is not None: insert.prev.next = insert

def insertAfter(insert:Node, after:Node):
    insert.next = after.next
    after.next = insert
    insert.prev = after
    if insert.next is not None: insert.next.prev = insert

class MedianFinder:
    
    def __init__(self):
        """
        initialize your data structure here.
        """
        self.left, self.right = None , None

    def addNum(self, num: int) -> None:
        node = Node(num)
        if self.left is None:
            self.left = node
            self.right = node
        elif self.left.val > node.val:
            cur = self.left
            while cur.prev is not None and cur.prev.val > node.val:
                cur = cur.prev
            insertBefore(node, cur)
            if self.left == self.right:
                self.left = self.left.prev
            else:
                self.right = self.left
        elif self.right.val < node.val:
            cur = self.right
            while cur.next is not None and cur.next.val < node.val:
                cur = cur.next
            insertAfter(node, cur)
            if self.left == self.right:
                self.right = self.right.next
            else:
                self.left = self.right
        else:
            insertAfter(node, self.left)
            if self.left == self.right:
                self.right = node
            else:
                self.left = self.right = node
                
    def findMedian(self) -> float:
        if self.left == self.right:
            return self.left.val
        else:
            return (self.left.val + self.right.val) / 2

class MedianFinder2:


    def __init__(self):
        """
        initialize your data structure here.
        """
        self.heapMin = []
        self.heapMax = []

    def addNum(self, num: int) -> None:
        if len(self.heapMin) == len(self.heapMax):
            if len(self.heapMax) > 0 and num > self.heapMax[0]:
                heapq.heappush(self.heapMin, -heapq.heappushpop(self.heapMax, num))
            else:
                heapq.heappush(self.heapMin, -num)
        else:
            if num > -self.heapMin[0]:
                heapq.heappush(self.heapMax, num)
            else:
                heapq.heappush(self.heapMax, -heapq.heappushpop(self.heapMin, -num))
            
                
    def findMedian(self) -> float:
        if len(self.heapMin) == len(self.heapMax):
            return (-self.heapMin[0] + self.heapMax[0]) / 2
        else:
            return -self.heapMin[0]

# Your MedianFinder object will be instantiated and called as such:
obj = MedianFinder2()
obj.addNum(-1)
print(obj.findMedian())
obj.addNum(-2)
print(obj.findMedian())
obj.addNum(-3)
print(obj.findMedian())
obj.addNum(-4)
print(obj.findMedian())
obj.addNum(-5)
print(obj.findMedian())
obj.addNum(15)
print(obj.findMedian())
obj.addNum(1)
print(obj.findMedian())
obj.addNum(11)
print(obj.findMedian())