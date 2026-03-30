import heapq
from sortedcontainers import SortedSet

class ExamRoom:

    def __init__(self, n: int):
        self.n = n
        self.taken = SortedSet()
        self.pq = [] # (-avail, l, r)

    def seat(self) -> int:
        def validate() -> bool:
            if self.pq[0][1] not in self.taken or self.pq[0][2] not in self.taken: return False
            inx = self.taken.index(self.pq[0][1])
            if inx == len(self.taken) - 1 or self.taken[inx + 1] != self.pq[0][2]:
                return False
            return True

        if len(self.taken) == 0:
            self.taken.add(0)
            return 0
        else:
            while self.pq and not validate(): heapq.heappop(self.pq) # 无效区间
            if (len(self.pq) == 0 or self.taken[0]-1 >= -self.pq[0][0]) and self.taken[0]-1>=self.n-2-self.taken[-1]:
                if self.taken[0] - 1: heapq.heappush(self.pq, (-((self.taken[0]-2)//2), 0, self.taken[0]))
                self.taken.add(0)
                return 0
            elif len(self.pq) > 0 and -self.pq[0][0] >= self.n-2-self.taken[-1]:
                _, l, r = heapq.heappop(self.pq)
                mid = (l + r) // 2
                if l + 1 < mid: heapq.heappush(self.pq, (-((mid-l-2)//2), l, mid))
                if mid + 1 < r: heapq.heappush(self.pq, (-((r-mid-2)//2), mid, r))
                self.taken.add(mid)
                return mid
            else:
                if self.n - 2 - self.taken[-1]:
                    heapq.heappush(self.pq, (-((self.n-3-self.taken[0])//2), self.taken[0], self.n-1))
                self.taken.add(self.n-1)
                return self.n - 1


    def leave(self, p: int) -> None:
        if p != self.taken[0] and p != self.taken[-1]: 
            inx = self.taken.index(p)
            l, r = self.taken[inx-1], self.taken[inx+1]
            heapq.heappush(self.pq, (-((r-l-2)//2), l, r))
        self.taken.remove(p)