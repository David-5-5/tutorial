from sortedcontainers import SortedList

class MKAverage:
    # 自行解答，可以通过
    # 但翻译成 C++ 超时
    def __init__(self, m: int, k: int):
        self.m = m
        self.k = k
        self.nums = []
        self.sorted = SortedList()
        self.sum = 0

    def addElement(self, num: int) -> None:
        self.nums.append(num)
        
        if len(self.nums) <= self.m:
            # 窗口未满时，直接插入并维护有序列表
            self.sorted.add((num, len(self.nums) - 1))
            if len(self.nums) == self.m:
                # 窗口满时，计算初始中间和
                for i in range(self.k, self.m - self.k):
                    self.sum += self.sorted[i][0]
        else:
            # 窗口已满，移除最旧元素，添加新元素
            out_idx = len(self.nums) - self.m - 1
            out_num = self.nums[out_idx]
            
            # 查找并移除最旧元素
            rm_pos = self.sorted.bisect_left((out_num, out_idx))
            removed = self.sorted.pop(rm_pos)
            
            # 根据移除元素的位置调整总和
            if self.k <= rm_pos <= self.m - self.k - 1:
                self.sum += self.sorted[self.m-self.k-1][0] - removed[0] 
            elif rm_pos < self.k:
                self.sum += self.sorted[self.m-self.k-1][0] - self.sorted[self.k-1][0]

            
            # 插入新元素
            ins_pos = self.sorted.bisect_left((num, len(self.nums) - 1))
            self.sorted.add((num, len(self.nums) - 1))
            
            # 根据新元素的位置调整总和
            if self.k <= ins_pos <= self.m - self.k - 1:
                self.sum += num - self.sorted[self.m-self.k][0]
            elif ins_pos < self.k:
                self.sum += self.sorted[self.k][0] - self.sorted[self.m-self.k][0]


    def calculateMKAverage(self) -> int:
        if len(self.nums) < self.m:
            return -1
        else:
            return self.sum // (self.m - 2 * self.k)


if __name__ == "__main__":
    sol = MKAverage(3, 1)
    print(sol.addElement(3))
    print(sol.addElement(1))
    print(sol.calculateMKAverage())
    print(sol.addElement(10))
    print(sol.calculateMKAverage())
    print(sol.addElement(5))
    print(sol.addElement(5))
    print(sol.addElement(5))
    print(sol.calculateMKAverage())
