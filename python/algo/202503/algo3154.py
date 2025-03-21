from functools import cache

# 动态规划 -  多维 DP
class Solution:
    def waysToReachStair(self, k: int) -> int:
        # 自行解答
        @cache
        def dfs(i:int, j:int, non:bool) -> int:
            # 递归终止：向下一步不能连续使用，且jump是指数增长。
            if i > k + 1: return 0  

            res = (i == k)
            # 不能连续使用
            if (i>0 and non): res += dfs(i-1, j, False)
            res += dfs(i+(1<<j), j+1, True)
            return res
        
        return dfs(1, 0, True)
