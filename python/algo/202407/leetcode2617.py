from math import inf
from typing import List

# 周赛 340
class Solution:
    def minimumVisitedCells(self, grid: List[List[int]]) -> int:
        # 参考题解 单调栈优化 DP
        # 动态规划转移方程为
        # f[i][j] = min{f[i][k] k in [j+1,j+g[i][j]]
        #               f[k][j] k in [i+1,i+g[i][j]]
        # 时间复杂度 O(mn(m+n)) 超时， 因此优化
        # 倒序递推 对于f[i][j] <= f[i][k] f[k][j] 的对于后续的转移是不必要的
        # 因此在行及列上定义单调栈，移动次数单调递增
        # 在程序实现上，有许多技巧需要掌握
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
                elif g: # g 大于 0 才能移动
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