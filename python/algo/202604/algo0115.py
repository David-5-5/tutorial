from functools import cache

class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        # 复习
        n, m = len(s), len(t)
        
        @cache
        def dfs(i:int, j:int) -> int:
            if i < j:return 0
            if j<0: return 1
            
            if s[i] == t[j]:
                return dfs(i-1, j-1) + dfs(i-1, j)
            else: return dfs(i-1, j)
        return dfs(n-1, m-1)
        