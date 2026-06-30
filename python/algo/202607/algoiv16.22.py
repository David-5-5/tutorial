from typing import List


class Solution:
    def printKMoves(self, K: int) -> List[str]:
        
        mx_r, mn_r, mx_c, mn_c = 0, 0, 0, 0
        r, c, d = 0, 0, 0
        grid = {}

        # clockwise d = (d+1) % 4, counterclockwise d = (d - 1) % 4
        # d = 0: c + 1  1 r - 1, c - 1 r + 1 
        DIR = ['R', 'D', 'L', 'U']

        while K:
            if (r, c) not in grid or grid[(r, c)] == '_':
                d = (d + 1) % 4
                grid[(r,c)] = 'X'
            else:
                d = (d - 1) % 4
                grid[(r,c)] = '_'
            if d == 0: c += 1
            elif d == 1: r -= 1
            elif d == 2: c -= 1
            else: r += 1
            if r > mx_r: mx_r = r
            if r < mn_r: mn_r = r
            if c > mx_c: mx_c = c
            if c < mn_c: mn_c = c
        
            K -= 1

        rows, cols = mx_r - mn_r + 1, mx_c - mn_c + 1
        ans = [[""] * cols for _ in range(rows)]
        for rr in range(rows):
            for cc in range(cols):
                if (rr+mn_r, cc+mn_c) in grid:
                    ans[rr][cc] = grid[(rr + mn_r,cc + mn_c)]
                else: ans[rr][cc] = "_"
        
        ans[r - mn_r][c - mn_c] = DIR[d]
        return ["".join(row) for row in ans][::-1]
