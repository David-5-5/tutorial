from random import shuffle
from typing import List

# 数学算法 - 随机算法 - 6.1 随机数
class Solution:

    def __init__(self, nums: List[int]):
        self.nums = nums

    def reset(self) -> List[int]:
        return self.nums

    def shuffle(self) -> List[int]:
        arr = self.nums.copy()
        shuffle(arr)
        return arr

