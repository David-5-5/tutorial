class Solution:
    def spiralOrder(self, matrix: list[list[int]]) -> list[int]:
        # 四边界收缩法
        m, n= len(matrix), len(matrix[0])
        left, right, top, bottom = 0, n-1, 0, m - 1

        ans, d = [], 0
        while left <= right and top <= bottom:
            if d == 0:
                for i in range(left, right+1):
                    ans.append(matrix[top][i])
                top += 1
            elif d == 1:
                for i in range(top, bottom+1):
                    ans.append(matrix[i][right])
                right -= 1
            elif d == 2:
                for i in range(right, left-1, -1):
                    ans.append(matrix[bottom][i])
                bottom -= 1
            else:
                for i in range(bottom, top-1, -1):
                    ans.append(matrix[i][left])
                left += 1
            d = (d + 1) % 4
        return ans        