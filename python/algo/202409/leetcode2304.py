from cmath import inf
from functools import cache
from typing import List

# 周赛 297
class Solution:
    def minPathCost(self, grid: List[List[int]], moveCost: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def dfs(r:int, c:int) -> int:
            if r == m-1: return grid[r][c]

            res = inf
            
            for c_n in range(n):
                res = min(res, grid[r][c] + moveCost[grid[r][c]][c_n] + dfs(r+1, c_n))
            
            return res

        return min(dfs(0, c) for c in range(n))
    
if __name__ == "__main__":
    sol = Solution()
    grid, moveCost = [[5,3],[4,0],[2,1]], [[9,8],[1,5],[10,12],[18,6],[2,4],[14,3]]
    print(sol.minPathCost(grid, moveCost))
