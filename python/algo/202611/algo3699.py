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

