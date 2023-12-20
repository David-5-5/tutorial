from typing import List, Callable
import math

def _build(func: Callable[[int, int], int], s: List[int], dp: List[int], l:int, r:int, p:int):
    if l == r:
        dp[p] = s[l]

    if r > l:
        mid = (l + r) // 2
        _build(func, s, dp, l, mid, p*2 +1)
        _build(func, s, dp, mid+1, r, p*2 +2)
        dp[p] = func(dp[p*2 + 1], dp[p*2 + 2])

def _length(n: int) -> int:
    return 2 ** (math.ceil(math.log(n, 2))+1) - 1


def _pushdown(func: Callable[[int, int], int], dp: List[int], t: List[int], pl:int, pr:int, p:int):
    mid = (pl + pr) // 2
    t[p*2+1], t[p*2+2], dp[p*2+1], dp[p*2+2] = t[p], t[p], t[p], t[p]
    for i in range(mid -pl): dp[p*2+1]=func(dp[p*2+1], t[p])
    for i in range(pr - mid - 1): dp[p*2+2]=func(dp[p*2+2], t[p])
    t[p] = 0

def _call_func(func: Callable[[int, int], int], dp: List[int],\
                t: List[int], l:int, r:int, pl:int, pr:int, p:int):
    if l <= pl and r >= pr:
        return dp[p]
    
    mid = (pl + pr) // 2
    if t[p]:
        _pushdown(func, dp, t, pl, pr, p)

    if mid >= r:
        return _call_func(func, dp, t, l, r, pl, mid, p*2 + 1)
    elif mid + 1 <= l:
        return _call_func(func, dp, t, l, r, mid+1, pr, p*2 + 2)
    else:
        return func(_call_func(func, dp, t, l, mid, pl, mid, p*2 + 1),  \
            _call_func(func, dp, t, mid+1, r, mid+1, pr, p*2 + 2))


def _update(func: Callable[[int, int], int], dp: List[int], t: List[int], \
            l:int, r:int, val: int,pl:int, pr:int, p:int):

    if l <= pl and r >= pr:
        dp[p] = val * (pr - pl + 1)
        t[p] = val
        return

    if t[p] and pl != pr:
        _pushdown(func, dp, t, pl, pr, p)

    mid = (pl + pr) // 2

    if mid >= r:
        _update(func, dp, t, l, r, val, pl, mid, p*2 + 1)
    elif mid + 1 <= l:
        _update(func, dp, t, l, r, val, mid+1, pr, p*2 + 2)
    else:
        _update(func, dp, t, l, r, val, pl, mid, p*2 + 1)
        _update(func, dp, t, l, r, val, mid+1, pr, p*2 + 2)
    dp[p] = func(dp[p*2 + 1], dp[p*2 + 2])


class SegmentTree:
    ''' Code segement tree following: https://oi-wiki.org/ds/seg/
    将固定的求和方法, 修改为函数参数, 函数需要满足结合律
    '''
    def __init__(self, s: List[int], func: Callable[[int, int], int]):
        self.n = len(s)
        self.dp = [-1] * _length(self.n)
        self.t = [0] * _length(self.n)
        self.func = func
        _build(func, s, self.dp, 0, len(s)-1, 0)

    def call_func(self, l:int, r:int):
        return _call_func(self.func, self.dp, self.t, l, r, 0, self.n-1, 0)

    def update(self, l:int, r:int, val: int,pl:int, pr:int, p:int):
        _update(self.func, self.dp, self.t, l, r, val, pl, pr, p)
        

if __name__ == "__main__":

    from datetime import datetime
    begin = datetime.now()
    for _ in range(1000):
        s = [i for i in range(1800)]
        dp = [-1] * _length(len(s))
        _build(lambda a,b:a+b, s, dp, 0, len(s)-1, 0)
    
    print((datetime.now()- begin).total_seconds())

    s = [i for i in range(16)]
    dp = [-1] * _length(len(s))
    t = [0] * len(dp)
    _build(lambda a,b:a+b, s, dp, 0, len(s)-1, 0)
    print(_call_func(lambda a,b:a+b, dp, t, 0, 15, 0, len(s)-1, 0))

    _update(lambda a,b:a+b, dp, t, 2, 14, 1, 0, len(s)-1, 0)
    print(_call_func(lambda a,b:a+b, dp, t, 10, 14, 0, len(s)-1, 0))
    print(_call_func(lambda a,b:a+b, dp, t, 0, 3, 0, len(s)-1, 0))
    print(_call_func(lambda a,b:a+b, dp, t, 0, 15, 0, len(s)-1, 0))

    st = SegmentTree(s, lambda a,b:a*b)
    print(st.call_func(2, 14))
    print(st.call_func(0, 14))


