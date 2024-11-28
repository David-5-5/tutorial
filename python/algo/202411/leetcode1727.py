from collections import defaultdict
from typing import List

# 贪心专题 先枚举，再贪心
class Solution:
    def largestSubmatrix(self, matrix: List[List[int]]) -> int:
        # 自行解答 超时 内存溢出
        rows, cols = len(matrix), len(matrix[0])

        mx = [defaultdict(int) for _ in range(rows)]

        ans = 0
        for c in range(cols):
            acc = 0
            for r in range(rows-1, -1, -1):
                if matrix[r][c] == 0:
                    acc = 0
                else:
                    acc += 1
                    dmat = mx[r]
                    for width in range(1, acc+1):
                        dmat[width] += 1
                        ans = max(ans, width * dmat[width])
        return ans
    
    def largestSubmatrix2(self, matrix: List[List[int]]) -> int:
        # 参考题解，进行预处理
        # 1，每列累计出现 1 的次数 (原地修改)
        # 2, 每行按次数排序，从小(高小宽大）到大(高大宽小）计算举行面积
        rows, cols = len(matrix), len(matrix[0])

        for r in range(1, rows):
            for c in range(cols):
                # 遇到matrix[r][c]=0 重新开始累计
                if matrix[r][c]: matrix[r][c] += matrix[r-1][c]
        
        ans = 0
        for r in range(rows):
            matrix[r].sort()
            for c in range(cols):
                ans = max(ans, matrix[r][c] * (cols-c))
        return ans


if __name__ == "__main__":
    sol = Solution()
    matrix = [[0,0,1],[1,1,1],[1,0,1]]
    print(sol.largestSubmatrix(matrix))
    print(sol.largestSubmatrix2(matrix))