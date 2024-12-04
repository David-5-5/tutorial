from functools import cache
from math import inf
from typing import List

# 双周赛 135
fmax = lambda x, y: x if x > y else y
class Solution:
    def maximumScore(self, grid: List[List[int]]) -> int:
        # 参考题解，还是不太明白
        n = len(grid)
        # 按列计算前缀和，initial = 0
        accs = [[0] * (n+1) for _ in range(n+1)]
        for r in range(n):
            for c in range(n):
                accs[c+1][r+1] = accs[c+1][r] + grid[r][c]
        
        dp1 = [0] * (n + 1)     # 前一列的行递减状态值
        dp2 = [-inf] * (n + 1)  # 前一列的行递增状态值
        
        for c in range(1, n + 1):
            ndp1 = [0] * (n + 1)
            ndp2 = [-inf] * (n + 1)
            
            for r in range(n + 1):
                for k in range(r, n + 1):
                    ndp1[k] = fmax(ndp1[k], dp1[r] + accs[c-1][k] - accs[c-1][r])
                for k in range(r + 1):
                    ndp2[k] = fmax(ndp2[k], dp2[r] + accs[c][r] - accs[c][k])
            # 一种情况：空了两列——此时这一行从 0 起步，ndp1[0]
            # 另一种情况：空了一列——此时这一行是 n 行起手，ndp[n] (前面做了交换 n,m 操作)
            ndp1[0] = fmax(ndp1[0], dp2[0])
            ndp1[n] = fmax(ndp1[n], dp2[0])
            # 这里是转移回递减的情况：从满了的增长变为减少
            ndp2[n] = fmax(ndp2[n], ndp1[n])
            dp1, dp2 = ndp1, ndp2
        return max(max(dp1), max(dp2))
        