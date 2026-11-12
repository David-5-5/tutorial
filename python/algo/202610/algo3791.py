from functools import cache


class Solution:
    def countBalanced(self, low: int, high: int) -> int:
        # 自行解答，数位 DP
        s_high = str(high)
        n = len(s_high)
        s_low = str(max(10, low)).rjust(n, '0')
        
        @cache
        def f(i:int, low_limit:bool, up_limit:bool, balance: int):
            if i == n:
                return 1 if balance == 0 else 0

            lo = int(s_low[i]) if low_limit else 0
            hi = int(s_high[i]) if up_limit else 9
            
            ans = 0
            for d in range(lo, hi+1):
                ans += f(i+1, low_limit and d==lo, up_limit and d==hi, 
                    balance + (-d if (n - i) % 2 else d)
                )
            return ans
        
        ans = f(0, True, True, 0)
        # f.cache_clear()
        return ans
