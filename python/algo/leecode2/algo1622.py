from typing import Callable
class Fancy:
    # 采用线段树方案，!!!!!! OVERTIME !!!!!!!!
    def pushdown(self, s, t, p):
        if s == t:
            while self.tp[p]:
                f = self.tp[p].pop(0)
                self.dp[p] = f(self.dp[p]) % (10 ** 9 + 7)
            return

        while self.tp[p]:
            f = self.tp[p].pop(0)
            self.tp[self.dp[p][0]].append(f)
            self.tp[self.dp[p][1]].append(f)

    # l is fixed 0
    def update(self, r:int, s:int, t:int, p:int, func: Callable[[int], int]):
        if 0 <= s and t <= r:
            self.tp[p].append(func)
            return

        m = s + ((t - s) >> 1)
        if self.tp[p] and s != t:
            self.pushdown(s, t, p)
        if 0 <= m:
            self.update(r, s, m, self.dp[p][0], func)
        if r > m:
            self.update(r, m + 1, t, self.dp[p][1], func)

    def insert(self, inx:int, s:int, t:int, p:int, value:int):
        # [l, r] 为修改区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
        if inx == s == t:
            self.dp[p] = value
            return
        # 当前区间为修改区间的子集时直接修改当前节点的值, 然后打标记, 结束修改
        m = s + ((t - s) >> 1)
        if inx <= m:
            if self.dp[p][0] == -1:
                self.dp[p][0] = len(self.dp)
                self.dp.append([-1,-1])
                self.tp.append([])
            self.insert(inx, s, m, self.dp[p][0], value)
        if inx > m:
            if self.dp[p][1] == -1:
                self.dp[p][1] = len(self.dp)
                self.dp.append([-1,-1])
                self.tp.append([])
            self.insert(inx, m + 1, t, self.dp[p][1], value)

    def get(self, inx:int, s:int, t:int, p:int):
        # [l, r] 为修改区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
        if self.tp[p]:
            self.pushdown(s, t, p)

        if inx == s == t:
            return self.dp[p]
        # 当前区间为修改区间的子集时直接修改当前节点的值, 然后打标记, 结束修改
        m = s + ((t - s) >> 1)
        if inx <= m:
            return self.get(inx, s, m, self.dp[p][0])
        if inx > m:
            return self.get(inx, m + 1, t, self.dp[p][1])

    def __init__(self):
        self.n = 10 ** 5
        self.cnt = 0
        self.dp = [[-1,-1]]
        self.tp = [[]] 

    def append(self, val: int) -> None:
        self.insert(self.cnt, 0, self.n-1, 0, val)
        self.cnt += 1

    def addAll(self, inc: int) -> None:
        if self.cnt - 1 < 0: return
        f = lambda a: a + inc
        self.update(self.cnt-1, 0, self.n-1, 0, f)

    def multAll(self, m: int) -> None:
        if self.cnt - 1 < 0: return
        f = lambda a: a * m
        self.update(self.cnt-1, 0, self.n-1, 0, f)

    def getIndex(self, idx: int) -> int:
        if idx >= self.cnt: return -1
        return self.get(idx, 0, self.n-1, 0)


class Fancy2:
    '''参考官方题解，
    keep small, keep quickly
    '''
    def __init__(self):
        self.MOD = 10 ** 9 + 7
        self.coeff = [[1, 0]]
        self.values = []

    def append(self, val: int) -> None:
        self.values.append(val)
        self.coeff.append([self.coeff[-1][0], self.coeff[-1][1]])

    def addAll(self, inc: int) -> None:
        # execute mod calculation, keep small        
        self.coeff[-1][1]= (self.coeff[-1][1]+inc) % self.MOD

    def multAll(self, m: int) -> None:
        # execute mod calculation, keep small        
        self.coeff[-1][0] = (self.coeff[-1][0] * m) % self.MOD
        self.coeff[-1][1] = (self.coeff[-1][1] * m) % self.MOD

    def getIndex(self, idx: int) -> int:
        if idx >= len(self.values): return -1
        
        # compute inverse
        a = (self.coeff[-1][0] * pow(self.coeff[idx][0], self.MOD-2, self.MOD)) % self.MOD
        b = self.coeff[-1][1] - a * self.coeff[idx][1]
        return (a * self.values[idx] + b) % self.MOD



if __name__ == "__main__":
    fancy = Fancy2()
    fancy.append(2)
    print(fancy.getIndex(0))
    fancy.multAll(3)
    fancy.append(9)
    fancy.append(6)
    fancy.append(10)
    fancy.append(5)
    fancy.append(10)
    fancy.append(5)
    print(fancy.getIndex(2))
    fancy.multAll(9)
    print(fancy.getIndex(0))
    fancy.multAll(5)
    fancy.addAll(8)
    fancy.append(2)
    fancy.multAll(10)
    fancy.append(2)
    fancy.append(5)
    fancy.addAll(8)
    fancy.multAll(4)
    fancy.append(8)
    fancy.append(10)
    fancy.multAll(4)
    fancy.append(3)
    print(fancy.getIndex(1))