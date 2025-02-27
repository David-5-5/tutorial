from functools import cache
from itertools import accumulate
from math import inf
from typing import List


class Solution:
    def minSpaceWastedKResizing(self, nums: List[int], k: int) -> int:
        # 参考题解，实质上就是将 nums 划分为 k + 1 段
        # 每段的的浪费空间是 区间的最大值 * 区间长度  - 区间和
        n = len(nums)
        
        pres = list(accumulate(nums, initial=0))
        mx_dis = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(i, n):
                if i == j: mx_dis[i][j] = nums[j]
                else: mx_dis[i][j] = max(mx_dis[i][j-1], nums[j])
        

        @cache
        def dfs(l:int, j:int) -> int:
            if j < 0: return inf
            if l == n: return 0

            return min(dfs(r+1, j-1) + mx_dis[l][r]*(r-l+1) - (pres[r+1]-pres[l]) for r in range(l,n))

        return dfs(0, k+1)
