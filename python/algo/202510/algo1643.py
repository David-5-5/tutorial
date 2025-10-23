from math import comb
from typing import List

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def kthSmallestPath(self, destination: List[int], k: int) -> str:
        v, h = destination # row 决定竖直方向 column 决定水平方向
        ans = []
        for _ in range(h+v):
            if h:
                o = comb(h+v-1, h-1) #
                if k > o:
                    ans.append('V')
                    v -= 1
                    k -= o
                else:
                    ans.append('H')
                    h -= 1
            else:
                ans.append('V')
                v -= 1
        return "".join(ans)    