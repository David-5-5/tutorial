from functools import cache

# 动态规划 -  多维 DP
class Solution:
    def waysToReachStair(self, k: int) -> int:

        @cache
        def dfs(i:int, j:int, non:bool) -> int:
            if i > k + 1: return 0

            res = (i == k)
            if (i>0 and non): res += dfs(i-1, j, False)
            res += dfs(i+(1<<j), j+1, True)
            return res
        
        return dfs(1, 0, True)
