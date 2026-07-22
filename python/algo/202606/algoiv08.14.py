from functools import cache
from typing import Tuple


class Solution:
    def countEval(self, s: str, result: int) -> int:
        # 从 c++ 自行转换过来
        
        @cache
        def dfs(expr: str) -> Tuple[int, int]:
            n = len(expr)
            if n == 1:
                return (1, 0) if expr=="0" else (0, 1)
            
            zero, one = 0, 0
            for i in range(1, n, 2):
                left_0, left_1 = dfs(expr[0:i])
                right_0, right_1 = dfs(expr[i+1:])

                if expr[i] == '^':
                    one += left_0 * right_1 + left_1 * right_0
                    zero += left_0 * right_0 + left_1 * right_1
                elif expr[i] == '&':
                    one += left_1 * right_1
                    zero += left_0 * right_0 + left_0 * right_1 + left_1 * right_0
                else:
                    one += left_1 * right_1 + left_0 * right_1 + left_1 * right_0
                    zero += left_0 * right_0 
            return (zero, one)

        zero, one = dfs(s)
        return one if result else zero