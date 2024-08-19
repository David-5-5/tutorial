from typing import List

# 双周赛 79
# 相比较标准的线段树求和，此题增加一个 min 数组，用于区段内记录每排占用人数的最小值
# 用于查找满足同一排观众 k  (m-min >= k) 的最小排
# 以及用于查找空余座位安排 (m-min>=1)
class BookMyShow:

    def __init__(self, n: int, m: int):
        size = (2 << n.bit_length()) - 1 # 2 ** (math.ceil(math.log(n, 2))+1) - 1
        self.st_sum = [0] * size # segment tree for sum
        self.st_min = [0] * size # segment tree for min
        self.n, self.m = n, m

    # 单点更新，加上指定的数
    def update(self, inx:int, val:int, s:int, t:int, p:int):
        if inx == s and inx == t:
            self.st_sum[p] += val
            self.st_min[p] += val
            return
        
        m = (s + t) // 2
        if inx <= m:
            self.update(inx, val, s, m, p*2+1)
        if inx > m:
            self.update(inx, val, m+1, t, p*2+2)
        
        self.st_sum[p] = self.st_sum[p*2+1] + self.st_sum[p*2+2]
        self.st_min[p] = min(self.st_min[p*2+1], self.st_min[p*2+2])

    # 区间求和
    def query(self, l:int, r:int, s:int, t:int, p:int) -> int:
        if l <= s and t <= r:
            return self.st_sum[p]

        m = (s + t) // 2
        res = 0
        if l <= m:
            res += self.query(l, r, s, m, p*2+1)
        if r > m:
            res += self.query(l, r, m+1, t, p*2+2)
        
        return res

    # 查找满足最小值的最小排
    def index(self, val:int, s:int, t:int, p:int) -> int:
        # 值越小表示剩余空间越大，即区间的剩余作为是否大于等于 k/1
        if self.st_min[p] > val: return -1 # p 区间的最小值大于指定值
        if s == t: return s
        m = (s + t) // 2
        ans = -1
        ans = self.index(val, s, m, p*2+1)
        if ans != -1: return ans  # 左节点优先
        ans = self.index(val, m+1, t, p*2+2)
        return ans

    def gather(self, k: int, maxRow: int) -> List[int]:
        inx = self.index(self.m - k, 0, self.n-1, 0) # self.m - k 指定最小值
        if inx == -1 or inx > maxRow : return []
        # inx 行的当前大小，即为起始的列
        c = self.query(inx, inx, 0, self.n-1, 0)
        self.update(inx, k, 0, self.n-1, 0)
        
        return [inx, c]


    def scatter(self, k: int, maxRow: int) -> bool:
        left = self.m * (maxRow+1) - self.query(0, maxRow, 0, self.n-1, 0)
        if left < k : return False
        
        while k:
            i = self.index(self.m-1, 0, self.n-1, 0) # self.m - 1 查找至少有一个空位的排
            left_s = self.m - self.query(i, i, 0, self.n-1, 0)
            self.update(i, min(left_s, k), 0, self.n-1, 0)
            k = k-left_s if k >= left_s else 0
        return True



# Your BookMyShow object will be instantiated and called as such:
# obj = BookMyShow(n, m)
# param_1 = obj.gather(k,maxRow)
# param_2 = obj.scatter(k,maxRow)

if __name__ == "__main__":
    # obj = BookMyShow(2, 5)
    # print(obj.gather(4,0))
    # print(obj.gather(2,0))
    # print(obj.scatter(5,1))
    # print(obj.scatter(5,1))
    obj = BookMyShow(18, 48)
    print(obj.scatter(24,13))
    print(obj.scatter(12,5))
    print(obj.gather(12,5))
    print(obj.scatter(3,12))
    print(obj.gather(36,13))
    print(obj.scatter(25,6))
    print(obj.scatter(32,14))
    print(obj.gather(29,6))
    print(obj.gather(3,11))
    print(obj.scatter(30,0))
    print(obj.gather(45,15))
    print(obj.gather(23,17))
    print(obj.gather(23,2))
    print(obj.scatter(41,10))
    print(obj.scatter(40,6))


