from typing import List

class TreeArray:
    __slots__ =('nums', 'tree')

    def __init__(self, nums:List[int]) -> None:
        self.nums = [0] * len(nums)
        self.tree = [0] * (len(nums) + 1)
        for i, num in enumerate(nums):
            self.update(i, num)

    def update(self, i:int, num:int):
        delta = num - self.nums[i]
        # tree array begin with 1
        ti = i + 1
        while ti < len(self.tree):
            self.tree[ti] += delta
            # the lowbit of ti is "ti & -ti"
            ti += ti & -ti # ti &= ti - 1 
    
    def _query(self, i:int):
        res = 0
        while i:
            res += self.tree[i]
            i -= i & -i
        return res

    def query(self, l:int, r:int) -> int:
        return self._query(r+1) - self._query(l)


# Inefficient implementation    
class TreeArray_II:
    __slots__ =('nums', 'tree')

    def __init__(self, nums:List[int]) -> None:
        self.nums = [0] * len(nums)
        self.tree = [0] * (len(nums) + 1)
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
        
        delta = num - self.nums[i]
        ti = i + 1
        self.tree[ti] += delta
        ti = (ti) + lowbit((ti))
        while ti < len(self.tree):
            self.tree[ti] += delta
            ti = ti + lowbit(ti)
    
    def _query(self, end:int):
        sinx = list(bin(end)[2:])
        inx = res = 0
        for i, v in enumerate(sinx):
            if v == '0': continue
            inx += 2 ** (len(sinx)-1-i)
            res += self.tree[inx]
        return res

    def query(self, l:int, r:int) -> int:
        return self._query(r+1) - self._query(l)




if __name__ == "__main__":
    from time import perf_counter
    time_start = perf_counter()
    ta = TreeArray([i+1 for i in range(10 ** 5)])
    print(ta.query(5000,10 ** 5-1))
    print(f'Took {perf_counter() - time_start} seconds')
    
    time_start = perf_counter() 
    ta2 = TreeArray_II([i+1 for i in range(10 ** 5)])
    print(ta2.query(5000,10 ** 5-1))
    print(f'Took {perf_counter() - time_start} seconds')


    from timeit import timeit
    
    def useTreeArray():
        ta = TreeArray([i+1 for i in range(10 ** 5)])

    time_duration = timeit('useTreeArray()',globals=globals(), number=10)
    print(f'Took {time_duration} seconds')

    def useTreeArrayII():
        ta = TreeArray_II([i+1 for i in range(10 ** 5)])
    time_duration = timeit('useTreeArrayII()', globals=globals(), number=10)
    print(f'Took {time_duration} seconds')
