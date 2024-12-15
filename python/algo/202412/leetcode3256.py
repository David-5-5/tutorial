from functools import cache
from math import inf
from typing import List

# 双周赛 137
class Solution:
    def maximumValueSum(self, board: List[List[int]]) -> int:
        # 自行解答，8486ms ，刚刚通过
        rows, cols = len(board), len(board[0])

        # 后缀最大值, 按列(最大的三行)
        # suf_mn = [[(-inf,-1),(-inf,-1),(-inf, -1)] for _ in range(cols)]
        # for c in range(cols-1, 1, -1):
        #     if c + 1 < cols: suf_mn[c] = suf_mn[c+1].copy()
        #     for r in range(rows):
        #         if r in [r for _, r in suf_mn[c]]:
        #             for i in range(3):
        #                 if suf_mn[c][i][1] == r and suf_mn[c][i][0] < board[r][c]:
        #                     suf_mn[c][i] = (board[r][c], r)
        #                     suf_mn[c].sort(reverse=True)
        #         else:
        #             if board[r][c] > suf_mn[c][0][0]:
        #                 suf_mn[c].insert(0, (board[r][c], r))
        #             elif board[r][c] > suf_mn[c][1][0]:
        #                 suf_mn[c].insert(1, (board[r][c], r))
        #             elif board[r][c] > suf_mn[c][2][0]:
        #                 suf_mn[c].insert(2, (board[r][c], r))
        #             del suf_mn[c][3:]
        # 
        # 
        # 后缀 按列统计的的行最大
        suf_mn = [[-inf] * rows for _ in range(cols)]
        for c in range(cols-1,-1,-1):
            for r in range(rows):
                suf_mn[c][r] = max(board[r][c], suf_mn[c+1][r] if c+1<cols else -inf)
        # 后缀 按列统计的的最大的三行，删除多余的行
        suf_mn_3 = [[] for _ in range(cols)]
        for c in range(cols):
            suf_mn_3[c] = [(v, r)for r, v in sorted(enumerate(suf_mn[c]), key=lambda p:-p[1])]
            del suf_mn_3[c][3:]

        @cache
        def dfs(c:int, r1:int, r2:int):
            if c == cols: return -inf

            
            if r1 != -1 and r2 != -1:
                for i in range(3):
                    if suf_mn_3[c][i][1] not in (r1,r2):
                        return suf_mn_3[c][i][0]
            
            res = -inf
            res = max(res, dfs(c+1, r1, r2)) # 不选
            if r1 == -1:
                res = max(res, max(board[i][c] + dfs(c+1,i, r2) for i in range(rows)))
            else:
                res = max(res, max(board[i][c] + dfs(c+1,r1, i) for i in range(rows) if i != r1))
            return res
        return dfs(0, -1, -1)