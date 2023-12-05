from typing import List
class Solution:
    def getMaxMatrix(self, matrix: List[List[int]]) -> List[int]:
        # 求二维数组/矩阵前缀和
        rows = len(matrix)
        cols = len(matrix[0])
        # 矩阵按列求一维数组的前缀和
        sum_by_col = [[0] * cols for _ in range(rows)]

        for i in range(rows):
            for j in range(cols):
                sum_by_col[i][j] = (sum_by_col[i-1][j] if i >0 else 0) + matrix[i][j]

        res = [-float("inf"), [-1, -1, -1, -1]]
        '''基于超时的算法, 降低一维, 固定上R1下边R2后, 将R1, R2之间的矩阵求和, 
        得到一维数组, 进行一维数组的最大连续求和, 参见算法algo 53
        '''
        # 求二维数组/矩阵任意子矩阵的和
        for r1 in range(rows):
            for r2 in range(r1, rows):
                begin = 0
                cum = sum_by_col[r2][0] - (sum_by_col[r1-1][0] if r1>0 else 0)
                if cum > res[0]:
                    res[0] = cum
                    res[1] = [r1, begin, r2, begin]
                for col in range(1, cols):
                    subsum = sum_by_col[r2][col] - \
                            (sum_by_col[r1-1][col] if r1>0 else 0)
                    if cum < 0:
                        cum = subsum
                        begin = col
                    else:
                        cum += subsum
                    
                    if cum > res[0]:
                        res[0] = cum
                        res[1] = [r1, begin, r2, col]
        
        return res[1]

    def getMaxMatrix_overtime(self, matrix: List[List[int]]) -> List[int]:
        '''!!!!!!!!!!!!!!OVERTIME!!!!!!!!!!!!!!!!!!
        '''
        # 求二维数组/矩阵前缀和
        rows = len(matrix)
        cols = len(matrix[0])
        presum = [[0] * cols for _ in range(rows)]

        for i in range(rows):
            for j in range(cols):
                presum[i][j] = (presum[i-1][j] if i>0 else 0) \
                    + (presum[i][j-1] if j>0 else 0) + \
                    - (presum[i-1][j-1] if i >0 and j>0 else 0) + matrix[i][j]

        res = [-float("inf"), [-1, -1, -1, -1]]
        # 求二维数组/矩阵任意子矩阵的和
        for r1 in range(rows):
            for c1 in range(cols):
                for r2 in range(r1, rows):
                    for c2 in range(c1, cols):
                        subsum = presum[r2][c2] - \
                                (presum[r1-1][c2] if r1>0 else 0) - \
                                (presum[r2][c1-1] if c1>0 else 0 ) + \
                                (presum[r1-1][c1-1] if r1>0 and c1>0 else 0)
                        if subsum > res[0]:
                            res[0] = subsum
                            res[1] = [r1, c1, r2, c2]
        
        return res[1]

if __name__ == "__main__":
    sol = Solution()
    matrix = [[-1, -2, -9, 6], 
              [8, -9, -3, -6], 
              [2, 9, -7, -6]]
    print(sol.getMaxMatrix(matrix))
    print(sol.getMaxMatrix_overtime(matrix))