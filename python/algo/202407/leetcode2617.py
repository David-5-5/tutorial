from math import inf
from typing import List


class Solution:
    def minimumVisitedCells(self, grid: List[List[int]]) -> int:
        
        m, n = len(grid), len(grid[0])

        col_st_l = [[] for _ in range(n)]

        def search(st, i):
            left = -1
            right = len(st)
            while left + 1 < right:
                mid = (left + right) // 2
                # st 是递减的
                if st[mid][1] <= i:
                    right = mid
                else:
                    left = mid
            return right

        mn = inf
        for i in range(m-1, -1, -1):
            row_st = []
            for j in range(n-1, -1, -1):
                col_st = col_st_l[j]
                g = grid[i][j]
                mn = inf
                
                if i == m-1 and j == n-1:
                    mn = 0
                elif g:
                    # 按列求最小值
                    k = i + g
                    k = search(col_st, k)
                    if 0 <= k < len(col_st):
                        mn = min(mn, col_st[k][0])

                    # 按行求最小值
                    k = j + g
                    k = search(row_st, k)
                    if 0 <= k < len(row_st):
                        mn = min(mn, row_st[k][0])

                if mn < inf:
                    mn += 1

                    while row_st and row_st[-1][0] >= mn:
                        row_st.pop()
                    row_st.append((mn, j))

                    while col_st and col_st[-1][0] >= mn:
                        col_st.pop()
                    col_st.append((mn, i))
        
        return mn if mn < inf else -1

if __name__ == "__main__":
    sol = Solution()
    grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
    print(sol.minimumVisitedCells(grid))