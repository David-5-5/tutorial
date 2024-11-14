from typing import List

# 周赛 367
class Solution:
    def constructProductMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        # 参考提示，前后缀分解
        MOD = 12345
        m, n = len(grid), len(grid[0])
        suffix = [[1] * n for _ in range(m)]
        
        for i in range(m*n-2, -1, -1):
            prev = i + 1
            suffix[i//n][i%n] = (suffix[prev//n][prev%n] * grid[prev//n][prev%n]) % MOD

        prefix = 1
        ans = [[1] * n for _ in range(m)]
        for i in range(n*m):
            ans[i//n][i%n] = (prefix * suffix[i//n][i%n]) % MOD
            prefix = (prefix * grid[i//n][i%n]) % MOD
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    grid = [[1,2],[3,4]]
    print(sol.constructProductMatrix(grid))   