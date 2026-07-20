from typing import List

# 
class Solution:
    def findSquare(self, matrix: List[List[int]]) -> List[int]:
        # 自行解答，前缀和
        n = len(matrix)

        row_pres = [[0] * (n+1) for _ in range(n)]
        col_pres = [[0] * (n) for _ in range(n+1)]
        for i in range(n):
            for j in range(n):
                row_pres[i][j+1] = row_pres[i][j] + matrix[i][j]
                col_pres[i+1][j] = col_pres[i][j] + matrix[i][j]

        ans = [-1, -1, 0]
        for i in range(n):
            for j in range(n):
                mx_s = min(n-i-1, n-j-1)
                for size in range(mx_s, -1 , -1):
                    if row_pres[i][j+size+1] - row_pres[i][j] == 0 and \
                        col_pres[i+size+1][j] - col_pres[i][j] == 0 and \
                        row_pres[i+size][j+size+1] - row_pres[i+size][j] == 0 and \
                        col_pres[i+size+1][j+size] - col_pres[i][j+size] == 0:
                        if size+1 > ans[2]:
                            ans = [i, j, size+1]
                        break

        return [] if ans[2] == 0 else ans


if __name__ == "__main__":
    matrix = [[1,0,1],[0,0,1],[0,0,1]]
    print(Solution().findSquare2(matrix))
