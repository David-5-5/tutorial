from math import inf
from typing import List

# 题单 矩形面积
class Solution:
    def numSubmat(self, mat: List[List[int]]) -> int:
        # 参考官方题解，方法一枚举
        n, m = len(mat), len(mat[0])

        row = [[0] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                if mat[i][j]:
                    row[i][j] = (row[i][j-1] if j > 0 else 0) + 1
                else:
                    row[i][j] = 0

        ans = 0
        for i in range(n):
            for j in range(m):
                col = row[i][j] # 以 (i,j) 为右下角的矩阵
                for k in range(i, -1, -1): # 从当前行遍历上面各行
                    col = min(col, row[k][j]) 
                    ans += col

        return ans

if __name__ == "__main__":
    sol = Solution()
    mat = [[1,0,1],[1,1,0],[1,1,0]]
    mat = [[0,1,1,0],[0,1,1,1],[1,1,1,0]]
    print(sol.numSubmat(mat))