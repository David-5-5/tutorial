from functools import cache


class Solution:
    def minDays(self, n: int) -> int:
        
        @cache
        def dfs(i: int) -> int:
            if i == 0: return 0

            res = i
            if i % 2 == 0: res = min(res, 1 + dfs(i // 2))
            else: res = min(res, 1 + dfs(i-1))
            
            if i % 3 == 0: res = min(res, 1 + dfs(i // 3))
            else: res = min(res, i % 3 + dfs(i - i % 3))

            return res
        
        return dfs(n)