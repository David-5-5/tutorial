from typing import List

# 常用数据结构 - 8.1 树状数组和线段树 - 树状数组
class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def update(self, i, delta):
        while i <= self.n:
            self.tree[i] += delta
            i += i & -i

    def query(self, i):
        result = 0
        while i > 0:
            result += self.tree[i]
            i -= i & -i
        return result

class NumArray:
    # 模板题
    def __init__(self, nums: List[int]):
        self.nums = nums
        self.ft = FenwickTree(len(nums))
        for i, d in enumerate(nums):
            self.ft.update(i+1, d)

    def update(self, index: int, val: int) -> None:
        delta = val - self.nums[index]
        self.nums[index] = val
        self.ft.update(index+1, delta)

    def sumRange(self, left: int, right: int) -> int:
        return self.ft.query(right+1) - self.ft.query(left)
        
