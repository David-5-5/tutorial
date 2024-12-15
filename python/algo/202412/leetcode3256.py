from functools import cache
from math import inf
from typing import List

# 双周赛 137
class Solution:
    def maximumValueSum(self, board: List[List[int]]) -> int:
        rows, cols = len(board), len(board[0])

        # suf_mn = [[(-inf,-1)(-inf,-1)(-inf, -1)] for _ in range(cols)]
        # for c in range(cols-1, 1, -1):
        #     for r in range(rows):
        #         if board[c]


        @cache
        def dfs(c:int, r1:int, r2:int):
            if c == cols: return -inf

            if r1 != -1 and r2 != -1:
                maxv = -inf
                for i in range(rows):
                    for j in range(c, cols):
                        if i in (r1, r2):continue
                        if board[i][j] > maxv: maxv = board[i][j]
                return maxv
            
            res = -inf
            res = max(res, dfs(c+1, r1, r2)) # 不选
            if r1 == -1:
                res = max(res, max(board[i][c] + dfs(c+1,i, r2) for i in range(rows)))
            else:
                res = max(res, max(board[i][c] + dfs(c+1,r1, i) for i in range(rows) if i != r1))
            return res
        return dfs(0, -1, -1)