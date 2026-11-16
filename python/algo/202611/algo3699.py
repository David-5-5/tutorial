from functools import cache
from itertools import accumulate


class Solution:
    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        # 自行解答 TLE O(n*(r-l)^2)
        mod = 10 ** 9 + 7
       
        @cache
        def dfs(i: int, prev: int, isCre: bool) -> int:
            if i == 0: return 1
            res = 0
            if i == n:  
                for nxt in range(l, r+1):
                    res += dfs(i-1, nxt, False)
            elif i == n-1:  
                for nxt in range(l, r+1):
                    if nxt == prev: continue
                    res += dfs(i-1, nxt, prev < nxt)
            elif isCre:
                for nxt in range(l, prev):
                    res += dfs(i-1, nxt, not isCre)
            else:
                for nxt in range(prev+1, r+1):
                    res += dfs(i-1, nxt, not isCre)

            res = res % mod
            return res
        
        ans = dfs(n, 0, False)
        dfs.cache_clear()
        return ans

    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        # 自行解答 递归 -> 递推 + 前缀和优化
        mod = 10 ** 9 + 7
        dp = [[[0] * (r-l+1) for _ in range(2)] for _ in range(2)]
        for v in range(0, r-l+1): dp[0][0][v] = 1

        pres = list(accumulate(dp[0][0], initial=0))
        for c in range(0, r-l+1):
            dp[1][1][c] = (pres[c] - pres[0]) % mod
            dp[1][0][c] = (pres[r-l+1] - pres[c+1]) % mod
        
        cur, prev = 0, 1
        for _ in range(2, n):
            pres_inc = list(accumulate(dp[prev][1], initial=0))
            pres_dec = list(accumulate(dp[prev][0], initial=0))
        
            for c in range(0, r-l+1):
                dp[cur][1][c] = (pres_dec[c] - pres_dec[0]) % mod
                dp[cur][0][c] = (pres_inc[r-l+1] - pres_inc[c+1]) % mod
            cur, prev = cur^1, prev^1

        return (sum(dp[prev][0]) + sum(dp[prev][1])) % mod