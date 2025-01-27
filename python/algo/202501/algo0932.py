from functools import cache
from typing import List

# 贪心专题 - 构造题
class Solution:
    def beautifulArray(self, n: int) -> List[int]:
        # 参考题解 分治 递归 比较难
        @cache
        def f(n: int) -> List[int] :
            if n == 1: return [1]

            res = []
            for x in f((n+1)//2):
                res.append(2*x-1)
            for x in f(n//2):
                res.append(2*x)

            return res
        return f(n)    