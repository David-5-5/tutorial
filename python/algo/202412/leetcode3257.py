from math import inf
from typing import List

# 双周赛 137
class Solution:
    def maximumValueSum(self, board: List[List[int]]) -> int:
        # 同 leetcode 3256 优化后方法
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