from functools import cache
from math import gcd


class Solution:
    def smallestNumber(self, num: str, t: int) -> str:
        # 参考题解 数位DP，有讲解豁然开朗
        cnt, tmp, primes = 0, t, [2,3,5,7]
        for p in primes:
            while tmp % p == 0:
                tmp /= p
                cnt += 1
        
        if tmp > 1: return "-1"

        cnt = max(cnt - len(num) + 1, 1)
        s = "0" * cnt + num
        n = len(s)
        ans = ['0'] * n

        @cache
        def dfs(i: int, t:int, isLimit: bool) -> bool:
            if i == n: return t == 1

            if isLimit and i < cnt and dfs(i+1, t, isLimit): return True

            low = int(s[i]) if isLimit else 0
            for d in range(max(low, 1), 10):
                ans[i] = str(d)
                if dfs(i+1, t // gcd(t, d), isLimit and low == d): return True
            return False

        dfs(0, t, True)
        dfs.cache_clear()
        return "".join(ans).lstrip("0") 