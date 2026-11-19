class Solution:
    def generateMatrix(self, n: int) -> list[list[int]]:
        left, right, top, bottom = 0, n-1, 0, n - 1

        matrix, d, cur = [[0] * n for _ in range(n)], 0, 1
        while left <= right and top <= bottom:
            if d == 0:
                for i in range(left, right+1):
                    matrix[top][i] = cur; cur += 1
                top += 1
            elif d == 1:
                for i in range(top, bottom+1):
                    matrix[i][right] = cur; cur += 1
                right -= 1
            elif d == 2:
                for i in range(right, left-1, -1):
                    matrix[bottom][i] = cur; cur += 1
                bottom -= 1
            else:
                for i in range(bottom, top-1, -1):
                    matrix[i][left] = cur; cur += 1
                left += 1
            d = (d + 1) % 4
        return matrix