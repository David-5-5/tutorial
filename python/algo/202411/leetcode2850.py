from itertools import permutations
from math import inf
from typing import List

# 周赛 362
class Solution:
    def minimumMoves(self, grid: List[List[int]]) -> int:
        # 参考题解，全排列
        from_, to_ = [], []
        for i in range(3):
            for j in range(3):
                c = grid[i][j]
                if c > 1:
                    from_.extend([(i,j)]*(c-1))
                elif c == 0:
                    to_.append((i, j))
        
        ans = inf
        for f2 in permutations(from_):
            cur = 0
            for (x1, y1), (x2,y2) in zip(f2, to_):
                cur  += abs(x1-x2) + abs(y1-y2)
            if ans > cur:ans = cur
        return ans

        
                