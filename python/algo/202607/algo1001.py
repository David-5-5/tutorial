from collections import defaultdict
from typing import List


class Solution:
    def gridIllumination(self, n: int, lamps: List[List[int]], queries: List[List[int]]) -> List[int]:
        DIRS = [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 0], [0, 1], [1, -1], [1, 0], [1, 1]]
        points = set()
        rows, cols, diag, anti = defaultdict(int), defaultdict(int), defaultdict(int), defaultdict(int)

        for l in lamps:
            r, c = l[0], l[1]
            if (r, c) not in points:
                points.add((r, c))
                rows[r] += 1
                cols[c] += 1
                diag[r - c] += 1
                anti[r + c ] += 1
        
        ans = [0] * len(queries)

        for i, q in enumerate(queries):
            r, c = q[0], q[1]
            if rows[r] or cols[c] or diag[r-c] or anti[r+c]:
                ans[i] = 1

            for d in DIRS:
                _r, _c = r + d[0], c + d[1]
                if 0 <= _r < n and 0 <= _c < n and (_r, _c) in points:
                    points.remove((_r, _c))
                    rows[_r] -= 1
                    cols[_c] -= 1
                    diag[_r - _c] -= 1
                    anti[_r + _c] -= 1
        return ans