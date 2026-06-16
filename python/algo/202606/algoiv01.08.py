from typing import List


class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m, n = len(matrix), len(matrix[0])

        rows, cols = set(), set()
        for i, row in enumerate(matrix):
            for j, v in enumerate(row):
                if v == 0:
                    rows.add(i)
                    cols.add(j)
        
        for r in rows:
            for j in range(n):
                matrix[r][j] = 0
        for c in cols:
            for i in range(m):
                matrix[i][c] = 0
