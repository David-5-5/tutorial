class StackOfPlates:

    def __init__(self, cap: int):
        self.cap = cap
        self.stacks = []

    def push(self, val: int) -> None:
        if self.cap == 0: return

        if len(self.stacks) == 0 or len(self.stacks[-1]) == self.cap:
            self.stacks.append([])
        self.stacks[-1].append(val)

    def pop(self) -> int:
        val = -1
        if self.cap == 0: return val
        if len(self.stacks): val = self.stacks[-1].pop()
        if len(self.stacks) and len(self.stacks[-1]) == 0:
            self.stacks.pop()
        return val

    def popAt(self, index: int) -> int:
        val = -1
        if self.cap == 0: return val
        
        if index < len(self.stacks):
            val = self.stacks[index].pop()
        if index < len(self.stacks) and len(self.stacks[index]) == 0:
            del self.stacks[index]
        return val                

