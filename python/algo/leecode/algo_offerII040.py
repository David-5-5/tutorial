# 主站 85
class Solution:
    # 题目变更为 LCR 040. 最大矩形
    def maximalRectangle(self, matrix) -> int:
        n = len(matrix)
        if n == 0: return 0
        m = len(matrix[0])

        left = [[0] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                if matrix[i][j] == '0':
                    left[i][j] = 0
                else:
                    left[i][j] = (left[i][j-1] if j > 0 else 0) + 1

        maxRect = 0
        for i in range(n):
            for j in range(m):
                width = []
                for k in range(i+1):
                    width.append(left[i - k][j])
                    maxRect = max(maxRect, min(width) * len(width))

        return maxRect


    def maximalRectangle2(self, matrix) -> int:
        n = len(matrix)
        if n == 0: return 0
        m = len(matrix[0])

        left = [[0] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                if matrix[i][j] == '0':
                    left[i][j] = 0
                else:
                    left[i][j] = (left[i][j-1] if j > 0 else 0) + 1

        maxRect = 0
        for j in range(m):
            stack = []
            for i in range(n):

                lens = 0
                while stack and stack[-1][0] > left[i][j]:
                    height, broad = stack.pop(-1)
                    lens += broad
                    maxRect = max(maxRect, height * lens)
                if left[i][j] > 0:
                    stack.append((left[i][j], lens + 1))

            lens = 0
            while stack:
                height, broad = stack.pop(-1)
                lens += broad
                maxRect = max(maxRect, height * lens)

        return maxRect


if __name__ == "__main__":
    sol = Solution()
    matrix =["10100","10111","11111","10010"]
    # matrix = ["11"]
    print(sol.maximalRectangle2(matrix))