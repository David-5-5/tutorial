from functools import cache

# 动态规划 - 11.1 前缀和优化 DP
class Solution:
    def new21Game(self, n: int, k: int, maxPts: int) -> float:
        
        @cache
        def dfs(i:int) -> float :
            if i > n : return 0
            if i >= k: return 1
            if i < k - 1:  # 关键条件，只有另一个合法才能相减
                return (dfs(i + 1) * (maxPts + 1) - dfs(i + 1 + maxPts)) / maxPts
            res = 0.0
            for inc in range(1, maxPts+1):
                res += dfs(inc+i)
            return res/maxPts
        return dfs(0)