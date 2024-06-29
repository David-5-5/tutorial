from collections import defaultdict
from typing import List

# https://leetcode.cn/problems/maximum-strictly-increasing-cells-in-a-matrix/submissions/542718160/
class Solution:
    def maxIncreasingCells(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        row_m = [0] * m
        col_m = [0] * n

        g = defaultdict(list)
        for i in range(m):
            for j in range(n):
                g[mat[i][j]].append([i,j])

        for _, pos in sorted(g.items(), key=lambda p:p[0]):

            mx = [max(row_m[i], col_m[j]) + 1 for i, j in pos]
            for (i, j), f in zip(pos, mx):
                row_m[i] = max(row_m[i], f)
                col_m[j] = max(col_m[j], f)
        
        return max(row_m)


if __name__ == "__main__":
    sol = Solution()
    mat = [[3,1],[3,4]]
    print(sol.maxIncreasingCells(mat))