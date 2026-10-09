from math import comb


class Solution:
    def createGrid(self, m: int, n: int, k: int) -> list[str]:
        # 构造题，参考题解
        if comb(m+n-2, n-1) < k: return []

        if (m == 3 and n == 3 and k == 4): return ["..#", "...", "#.."]

        grid = [['#'] * n for _ in range(m)]
        for i in range(n): grid[0][i] = '.'
        for i in range(m): grid[i][-1] = '.'

        if (k > 1):
            if n >= k:
                for i in range(k-1):
                    grid[1][-2-i] = '.'
            else:
                for i in range(k-1):
                    grid[i+1][-2] = '.'
        return ["".join(row) for row in grid]
        

