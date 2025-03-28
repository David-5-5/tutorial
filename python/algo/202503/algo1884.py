from functools import cache
from math import inf

# 动态规划 - 多维 DP
class Solution:
    def twoEggDrop(self, n: int) -> int:
        # 自行解答 - 性能需要优化
        @cache
        def dfs(i: int, j:int, k:int) -> int:
            if k == 0: return inf
            if k == 1: return j - i + 1
            if i > j: return 0

            res = inf
            for t in range(i, j+1):
                res = min(res, 1 + max(dfs(t+1, j, k),dfs(i, t-1, k-1)))
            return res
        ans = dfs(1, n, 2)
        dfs.cache_clear()
        return ans


    def twoEggDrop(self, n: int) -> int:
        # 自行解答 - 优化
        @cache
        def dfs(i: int) -> int:
            if i == 1: return 1

            res = inf
            for t in range(1, i):
                res = min(res, max(1+dfs(i-t), t))
            return res
        ans = dfs(n)
        return ans