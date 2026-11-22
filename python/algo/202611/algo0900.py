class RLEIterator:

    def __init__(self, encoding: list[int]):
        self.enc = encoding[::-1]        

    def next(self, n: int) -> int:
        while len(self.enc) and self.enc[-1] < n:
            n -= self.enc[-1]
            del self.enc[-2:]

        if len(self.enc) == 0: return -1
        val = self.enc[-2]
        self.enc[-1] -= n
        if self.enc[-1] == 0:
            del self.enc[-2:]
        return val
        


# Your RLEIterator object will be instantiated and called as such:
# obj = RLEIterator(encoding)
# param_1 = obj.next(n)