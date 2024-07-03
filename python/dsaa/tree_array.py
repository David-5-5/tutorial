from typing import List


class TreeArray:
    

    def __init__(self, nums:List[int]) -> None:
        self.n = len(nums)
        self.tree = [0] * (self.n+1)
        for i, num in enumerate(nums):
            self.update(i, num)

    def update(self, i:int, num:int):
        def lowbit(v:int) -> int:
            if  v == 0: return 0
            low = 0
            while v & 1 != 1:
                v >>= 1
                low += 1
            return 2 ** low
        
        self.tree[i+1] += num
        next = (i+1) + lowbit((i+1))
        while next < self.n:
            self.tree[next] += num
            next = next + lowbit(next)
    
    def _query(self, end:int):
        sinx = list(bin(end)[2:])
        inx = res = 0
        for i, v in enumerate(sinx):
            inx += 2 ** (len(sinx)-1-i) if v else 0
            res += self.tree[inx]
        return res

    def query(self, l:int, r:int) -> int:
        return self._query(r) - self._query(l-1)


if __name__ == "__main__":
    ta = TreeArray([i+1 for i in range(16)])
    print(ta.query(1,16))
    