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

    def stoneGameVIII2(self, stones: List[int]) -> int:
        # 自行解答，递归 - > 迭代（递推） -> 优化
        n = len(stones)
        pres = list(accumulate(stones, initial=0))

        f = [-inf] * (n)
        f[n-1] = pres[n]        # 初始化
        for i in range(n-2,0,-1):            
            # 二次循环
            # for j in range(i, n):     # 迭代（递推）
            #     f[i] = max(f[i], pres[j+1] - f[j+1])
            
            # 优化后 写法一
            f[i] = max(f[i+1], pres[i+1] - f[i+1])
            
            # 写法二，不用 max 函数，性能更优
            # val = pres[i+1] - f[i+1]
            # if f[i+1] > val:
            #     f[i] = f[i+1]
            # else: f[i] = val
                        

        return f[1]
