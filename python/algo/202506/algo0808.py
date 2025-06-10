from functools import cache

# 动态规划 - 15. 概率/期望 DP
class Solution:
    def soupServings(self, n: int) -> float:
        # 动态规划部分自行解答， 数学部分参考题解
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

    def soupServings2(self, n: int) -> float:
        # 进一步优化，步长 25 -> 1
        # n = 10^9，但是当 n 到达一定值之后 答案接近于 1
        # 因此当 n 大于某个值时，直接返回 1

        if n > 180*25: return 1  # 
        n = n//25 + (n%25 != 0)

        # n 为 较小值时，使用动态规划，记忆化搜索
        @cache
        def dfs(a:int, b:int) -> float:
            if a > 0 and b <= 0: return 0
            if a <= 0 and b > 0: return 1.0
            if a <= 0 and b <= 0: return 0.5

            res = 0
            for x, y in (4, 0), (3, 1), (2, 2), (1, 3):
                res += dfs(a-x, b-y)
            
            return res / 4
        return dfs(n, n)
