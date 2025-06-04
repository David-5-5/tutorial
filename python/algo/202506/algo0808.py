from functools import cache

# 动态规划 - 15. 概率/期望 DP
class Solution:
    def soupServings(self, n: int) -> float:
        
        # n = 10^9，但是当 n 到达一定值之后 答案接近于 1
        # 因此当 n 大于某个值时，直接返回 1
        if n > 180 * 25 : return 1  # 

        # n 为 较小值时，使用动态规划，记忆化搜索
        @cache
        def dfs(a:int, b:int) -> float:
            if a > 0 and b <= 0: return 0
            if a <= 0 and b > 0: return 1.0
            if a <= 0 and b <= 0: return 0.5

            res = 0
            for x, y in (100, 0), (75, 25), (50, 50), (25, 75):
                res += dfs(a-x, b-y)
            
            return res / 4
        return dfs(n, n)
