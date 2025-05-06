from functools import cache

# 动态规划 - 数位 DP
class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        # 自行解答
        sl, sr = str(l), str(r)
        n = len(sr)
        diff = n - len(sl)

        @cache
        def f(i:int, mul:int, sum:int, is_low:bool, is_high:bool, is_num:bool) -> int:
            if (i == n):
                return is_num and mul % sum == 0
            
            lo = int(sl[i-diff]) if is_low and i>=diff else 0
            hi = int(sr[i]) if is_high else 9

            res = 0
            for d in range(lo, hi+1):
                if not is_num and d == 0:
                    res += f(i+1, mul, sum, is_low and d==lo, is_high and d==hi, False)
                else:
                    res += f(i+1, mul*d, sum+d, is_low and d==lo, is_high and d==hi, True)
            return res
        return f(0, 1, 0, True, True, False)