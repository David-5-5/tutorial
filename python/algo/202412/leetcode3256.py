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
        suf_mx = [[-inf] * rows for _ in range(cols)]
        for c in range(cols-1,-1,-1):
            for r in range(rows):
                suf_mx[c][r] = max(board[r][c], suf_mx[c+1][r] if c+1<cols else -inf)
        # 后缀 按列统计的的最大的三行，删除多余的行
        suf_mx_3 = [[] for _ in range(cols)]
        for c in range(cols):
            suf_mx_3[c] = [(v, r)for r, v in sorted(enumerate(suf_mx[c]), key=lambda p:-p[1])]
            del suf_mx_3[c][3:]

        @cache
        def dfs(c:int, r1:int, r2:int):
            if c == cols: return -inf

            
            if r1 != -1 and r2 != -1:
                for i in range(3):
                    if suf_mx_3[c][i][1] not in (r1,r2):
                        return suf_mx_3[c][i][0]
            
            res = -inf
            res = max(res, dfs(c+1, r1, r2)) # 不选
            if r1 == -1:
                res = max(res, max(board[i][c] + dfs(c+1,i, r2) for i in range(rows)))
            else:
                res = max(res, max(board[i][c] + dfs(c+1,r1, i) for i in range(rows) if i != r1))
            return res
        return dfs(0, -1, -1)
    

    def maximumValueSum2(self, board: List[List[int]]) -> int:
        # 进一步优化，计算前后缀最大值
        rows, cols = len(board), len(board[0])

        # 按行统计 每行的最大三个值
        board_3 = [[] for _ in range(rows)]
        for r in range(rows):
            board_3[r] = [(v, c)for c, v in sorted(enumerate(board[r]), key=lambda p:-p[1])]
            del board_3[r][3:]

        
        # 按行分组 计算每行的前缀最大值
        pre_mx = [[-inf] * cols for _ in range(rows)]
        for r in range(rows):
            for c in range(cols):
                pre_mx[r][c] = max(board[r][c], pre_mx[r-1][c] if r>0 else -inf)
        # 前缀 按列统计的的最大的三行，删除多余的行
        pre_mx_3 = [[] for _ in range(rows)]
        for r in range(rows):
            pre_mx_3[r] = [(v, c)for c, v in sorted(enumerate(pre_mx[r]), key=lambda p:-p[1])]
            del pre_mx_3[r][3:]

        # 按列分组 计算每行的后缀最大值
        suf_mx = [[-inf] * cols for _ in range(rows)]
        for r in range(rows-1,-1,-1):
            for c in range(cols):
                suf_mx[r][c] = max(board[r][c], suf_mx[r+1][c] if r+1<rows else -inf)
        # 后缀 按列统计的的最大的三行，删除多余的行
        suf_mx_3 = [[] for _ in range(rows)]
        for r in range(rows):
            suf_mx_3[r] = [(v, c)for c, v in sorted(enumerate(suf_mx[r]), key=lambda p:-p[1])]
            del suf_mx_3[r][3:]

        ans = -inf
        for midr in range(1, rows-1):
            for mid_v, mid_c in board_3[midr]:
                for pre_v, pre_c in pre_mx_3[midr-1]:
                    if pre_c != mid_c:
                        for suf_v, suf_c in suf_mx_3[midr+1]:
                            if suf_c not in (mid_c, pre_c):
                                if pre_v + mid_v + suf_v > ans:
                                    ans = pre_v + mid_v + suf_v
                                break

        return ans