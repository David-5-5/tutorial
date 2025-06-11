from functools import cache

# 动态规划 - 15. 概率/期望 DP
class Solution:
    def knightProbability(self, n: int, k: int, row: int, column: int) -> float:
        
        @cache
        def dfs(r:int, c:int, left:int) -> float :
            if r < 0 or r >= n or c < 0 or c >=n: return 0
            if left == 0: return 1

            res = 0
            for x, y in [(-2,-1),(-1,-2),(1,-2),(2,-1),(-2,1),(-1,2),(1,2),(2,1)]:
                res += dfs(r+x, c+y, left-1)
            return res/8
        return dfs(row, column, k)