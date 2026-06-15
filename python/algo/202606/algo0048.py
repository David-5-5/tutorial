from typing import List

# 旋转
class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        for i in range(n//2):
            for j in range(i, n-i-1):
                x, y = i, j
                cur = matrix[x][y]
                for _ in range(4):
                    nxt = matrix[y][n-x-1]
                    matrix[y][n-x-1] = cur
                    cur, x, y = nxt, y, n-x-1

    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        # 更简洁
        for i in range(n//2):
            for j in range(i, n-i-1):
                tmp = matrix[i][j]
                matrix[i][j] = matrix[n-j-1][i]
                matrix[n-j-1][i] = matrix[n-i-1][n-j-1]
                matrix[n-i-1][n-j-1] = matrix[j][n-i-1]
                matrix[j][n-i-1] = tmp