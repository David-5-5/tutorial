from collections import defaultdict
import random
from typing import List

# 数学算法 - 随机算法 - 6.1 随机数
class Solution:
    # 自行解答 随机函数
    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.t_inxs = defaultdict(list)
        for i, v in enumerate(nums): self.t_inxs[v].append(i)
        random.seed(100)
            

    def pick(self, target: int) -> int:
        inx = random.randint(0, self.n) % len(self.t_inxs[target])
        return self.t_inxs[target][inx]
    