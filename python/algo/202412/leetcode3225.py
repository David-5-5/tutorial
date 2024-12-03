from functools import cache
from typing import List

# 双周赛 135
class Solution:
    def maximumScore(self, grid: List[List[int]]) -> int:
        n = len(grid)
        # 按列计算前缀和，initial = 0
        presum = [[0] * n for _ in range(n+1)]
        for r in n:
            for c in n:
                presum[r+1][c] = presum[r][c] + grid[r][c]
        

        @cache
        def dfs(c:int, r:int, t: bool) ->int:
            if r == 0: return 0 # 一行未涂，返回

