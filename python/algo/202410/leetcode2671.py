from bisect import bisect_left
from collections import defaultdict


class FrequencyTracker:

    def __init__(self):
        self.n_2_f = defaultdict(int)
        self.freq = defaultdict(list)

    def add(self, number: int) -> None:
        f = self.n_2_f[number]
        if f:
            inx = bisect_left(self.freq[f], number)
            del self.freq[f][inx]
        
        self.n_2_f[number] += 1
        inx = bisect_left(self.freq[f+1], number)
        self.freq[f+1].insert(inx, number)
        


    def deleteOne(self, number: int) -> None:

        f = self.n_2_f[number]
        if f == 0: return

        inx = bisect_left(self.freq[f], number)
        del self.freq[f][inx]

        self.n_2_f[number] -= 1
        if self.n_2_f[number]:
            inx = bisect_left(self.freq[f-1], number)
            self.freq[f-1].insert(inx, number)

       
    def hasFrequency(self, frequency: int) -> bool:
        if self.freq[frequency]: return True
        return False


# Your FrequencyTracker object will be instantiated and called as such:
obj = FrequencyTracker()
obj.add(1)
obj.add(1)
print(obj.hasFrequency(1))