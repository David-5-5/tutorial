from cmath import inf
from functools import cache
from typing import List


class Solution:
    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        # 复习 递归 超时
        n = len(nums)

        pres_n, pres_c, sufs, = [0] * (n+1), [0] * (n+1), [0] * (n+1)
        for i in range(n):
            pres_n[i+1] = pres_n[i] + nums[i]
            pres_c[i+1] = pres_c[i] + cost[i]
            sufs[n-i-1] = sufs[n-i] + cost[n-i-1]
        
        @cache
        def dfs(l:int, r:int) -> int:
            if l == 0:
                return pres_n[r+1] * (pres_c[r+1]-pres_c[l]) + k * sufs[l]

            return min(dfs(l-1, r), dfs(l-1, l-1) + pres_n[r+1] * (pres_c[r+1]-pres_c[l]) + k * sufs[l])
        ans = dfs(n-1, n-1)
        dfs.cache_clear()
        return ans

    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        # 递归 -> 递推 AC
        n = len(nums)
        
        pres_n, pres_c, sufs, = [0] * (n+1), [0] * (n+1), [0] * (n+1)
        for i in range(n):
            pres_n[i+1] = pres_n[i] + nums[i]
            pres_c[i+1] = pres_c[i] + cost[i]
            sufs[n-i-1] = sufs[n-i] + cost[n-i-1]
        
        f = [[inf] * n for _ in range(n)]
        for r in range(n):
            f[0][r] = pres_n[r+1] * (pres_c[r+1]-pres_c[0]) + k * sufs[0]
        for r in range(n):
            for l in range(1, r+1):
                f[l][r] = min(f[l-1][r], f[l-1][l-1] + pres_n[r+1] * (pres_c[r+1]-pres_c[l]) + k * sufs[l])
        return f[n-1][n-1]

