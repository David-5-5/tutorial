class SortedStack:

    def __init__(self):
        self.stack = []

    def push(self, val: int) -> None:
        tmp = []
        while self.stack and self.stack[-1] < val:
            tmp.append(self.stack.pop())
        self.stack.append(val)

        while tmp:
            self.stack.append(tmp.pop())

    def pop(self) -> None:
        if self.stack: self.stack.pop()

    def peek(self) -> int:
        if not self.stack: return -1
        return self.stack[-1]

    def isEmpty(self) -> bool:
        return not self.stack



# Your SortedStack object will be instantiated and called as such:
# obj = SortedStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.peek()
# param_4 = obj.isEmpty()