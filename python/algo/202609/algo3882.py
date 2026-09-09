from cmath import inf
from functools import cache
from typing import List

class Solution:
    def minCost(self, grid: list[list[int]]) -> int:
        # 基于 3393 的思路，统计异或值为给定值的路径数目
        # 从高位到低位，逐步掩码计算是否存在该位为 0 的值，存在，改位设为0，否则该位为 1.
        m, n = len(grid), len(grid[0])
        
        mask, target = 0, 0
        for i in range(9, -1, -1):
            mask |= 1 << i
            # 3393 异或值为指定值
            @cache
            def dfs(i: int, j:int, p:int) -> bool:
                if i >= m or j >= n: return False
                if i == m-1 and j == n-1:
                    if p ^ (grid[i][j] &mask) == target: return True
                    else: return False
                
                if dfs(i+1,j,p^(grid[i][j] & mask)): return True
                if dfs(i,j+1,p^(grid[i][j] & mask)): return True
                return False
            if not dfs(0,0,0): target |= 1 << i     # 不存在为 0 的路径，该位设置为 1
        return target

    def minCost(self, grid: list[list[int]]) -> int:
        # 剪枝
        m, n = len(grid), len(grid[0])
        vis, ans = set(), inf

        def dfs(i: int, j:int, xor:int):
            nonlocal ans
            if i >= m or j >= n or ans == 0 or (i, j, xor) in vis: return

            vis.add((i, j, xor))
            xor ^= grid[i][j]

            if i == m-1 and j == n-1:
                ans = min(ans, xor)
                return
            
            dfs(i+1,j, xor)
            dfs(i,j+1, xor)
        dfs(0,0,0)
        return ans
