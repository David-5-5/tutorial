from asyncio import log
from cmath import inf
from functools import cache


class Solution:
    def leastOpsExpressTarget(self, x: int, target: int) -> int:
        
        @cache
        def dfs(left: int) -> int:
            if left == 0 or left == x: return 0
            if left == 1: return 1

            if left < x:
                return min(1 + (x-left)*2-1, left*2 -1 )

            p = int(log(left, 2) // log(x, 2))
            res = inf
            # 乘法
            if pow(x, p) == left:
                res = min(res, p-1)
            else:
                if left-int(pow(x, p)) < left:
                    res = min(res, p + dfs(left-int(pow(x, p))))
                if int(pow(x,p+1)) - left < left:
                    res = min(res, p + 1 + dfs(int(pow(x,p+1)) - left))
            # 加法
            if left % x == 0:
                res = min(res, left//x - 1)
            else:
                res = min(res, left//x + dfs(left % x))
                res = min(res, left//x + 1 + dfs(x - left % x))

            # 除法
            res = min(res, left * 2 - 1)

            return res

        return dfs(target)