from functools import cache
from typing import List


class Solution:
    def domino(self, n: int, m: int, broken: List[List[int]]) -> int:
        # 自行解答
        if len(broken) == 0: return n * m // 2

        r_mask = [0] * n
        for x, y in broken:
            r_mask[x] |= 1 << y
            
        @cache
        def dfs(r: int, mask) -> int:
            if r == n: return 0

            result = []
            def enum(c: int, nr_mask, cnt):
                if c == m:
                    result.append([nr_mask, cnt])
                    return
                enum(c+1, nr_mask, cnt) # skip
                if c < m-1 and (mask >> c) & 1 == 0 and (mask >> (c+1)) & 1 == 0:
                    enum(c+2, nr_mask, cnt + 1)
                if (mask >> c) & 1 == 0 and (nr_mask >> c) & 1 == 0:
                    enum(c+1, nr_mask | 1 << c, cnt + 1)
            nr_mask = (1 << m) - 1
            
            if r < n - 1: nr_mask = r_mask[r+1]
            enum(0, nr_mask, 0)
            return max([cnt + dfs(r+1, nr_mask) for nr_mask, cnt in result])

        return dfs(0, r_mask[0])


