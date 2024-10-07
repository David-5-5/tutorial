from typing import List

# 双周赛 129
class Solution:
    def numberOfRightTriangles(self, grid: List[List[int]]) -> int:
        # 自行解答
        m, n = len(grid), len(grid[0])

        row, col = [0] * m, [0] * n
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    row[r] += 1
                    col[c] += 1
        ans = 0
        for r in range(m):
            for c in range(n):
                if grid[r][c] == 1:
                    ans += (row[r] - 1) * (col[c] - 1)
        
        return ans

if __name__ == "__main__":
    sol = Solution()
    grid = [[0,1,0],[0,1,1],[0,1,0]]
    print(sol.numberOfRightTriangles(grid))
    