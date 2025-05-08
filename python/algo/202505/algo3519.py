from functools import cache
from typing import List

# 动态规划 - 数位 DP
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        mod = 10 ** 9 + 7
        def trans(s: str) -> List[int]:
            res = []
            num = int(s)
            while num:
                num, rem = divmod(num, b)
                res.append(rem)
            return res[::-1]
    
        lows, highs = trans(l), trans(r)
        n = len(highs)
        diff = n - len(lows)

        @cache
        def f(i:int, p: int, is_low: bool, is_high:bool) -> int:
            if i == n:return 1

            lo = lows[i-diff] if is_low and i>=diff else 0
            hi = highs[i] if is_high  else b - 1

            res = 0
            for d in range(max(lo, p), hi+1):
                res = (res + f(i+1, d, is_low and d == lo, is_high and d==hi)) % mod
            return res
        
        return f(0, 0, True, True)