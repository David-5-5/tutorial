from cmath import inf
from functools import cache
from itertools import accumulate
from typing import List

# 动态规划 - 14. 博弈 DP
class Solution:
    def stoneGameVIII(self, stones: List[int]) -> int:
        # 自行解答，记忆化搜索- overtime
        n = len(stones)
        pres = list(accumulate(stones, initial=0))

        @cache
        def dfs(i:int) -> int:
            if i == n: return 0
            res = -inf

            for j in range(i, n):
                res = max(res, pres[j+1] - dfs(j+1))
            
            return res

        return dfs(1)

