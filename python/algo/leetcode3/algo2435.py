from functools import lru_cache
from typing import List

# 周赛 314
MOD = 10 ** 9 + 7

class Solution:
    def numberOfPaths(self, grid: List[List[int]], k: int) -> int:
        m ,n = len(grid), len(grid[0])

        @lru_cache(maxsize=None)
        def dfs(i: int, j: int, g: int) -> int:
            if i < 0 or j < 0:return 0

            if i == 0 and j == 0 and (g + grid[i][j]) % k == 0:
                return 1
            
            return (dfs(i - 1, j, (g + grid[i][j]) % k) + dfs(i, j - 1, (g + grid[i][j]) % k)) % MOD
        
        ans = dfs(m-1,n-1, 0)% MOD
        dfs.cache_clear()
        return ans

    def numberOfPaths2(self, grid: List[List[int]], k: int) -> int:
        # 根据上面的递归方法，导出递推公式
        m ,n = len(grid), len(grid[0])

        dp = [[[0] * k for _ in range(n)] for _ in range(m)]

        dp[0][0][grid[0][0]% k] = 1
        for i in range(m):
            for j in range(n):
                if i == 0 and j==0:
                    continue
                for g in range(k):
                    dp[i][j][g] = ((dp[i - 1][j][(g + k - grid[i][j]% k) % k] if i>0 else 0) + 
                                   (dp[i][j - 1][(g + k - grid[i][j]% k) % k] if j>0 else 0)) % MOD
        
        return dp[-1][-1][0]% MOD

if __name__ == "__main__":
    grid = [[5,2,4],[3,0,5],[0,7,2]]
    k = 3
    # grid, k= [[0,0]] , 5

    print(f"{grid} with k={k} has {Solution().numberOfPaths2(grid, k)} paths")
