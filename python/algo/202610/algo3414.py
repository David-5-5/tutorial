from bisect import bisect_left
from functools import cache
from typing import List

from torch import inf


class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        # brute, TLE
        idx = [i for i, _  in sorted(enumerate(intervals), key=lambda p:p[1]) ]
        intervals.sort()
        
        n = len(intervals)
        @cache
        def dfs(i: int, j: int, k: int) -> int:
            if k == 0 or i == n: return 0
            l, r, w = intervals[i]

            if j>=0 and l <= intervals[j][1]:
                return dfs(i+1, j, k)

            return max(intervals[i][2] + dfs(i+1, i, k-1), dfs(i+1, j, k))
        
        mx = dfs(0, -1, 4)
        
        def trace(i: int, j: int, k: int, score: int) -> List[int]:
            if k == 0 or i == n: return []
            l, _, _ = intervals[i]

            if j>=0 and l <= intervals[j][1]:
                return trace(i+1, j, k, score)
            
            sel, n_sel = False, False
            if intervals[i][2] + dfs(i+1, i, k-1) == score:
                sel = True
                res1 = [idx[i]] + trace(i+1, i, k-1, score-intervals[i][2])
                res1.sort()
            if dfs(i+1, j, k) == score:
                n_sel = True
                res2 = trace(i+1, j, k, score)
                res2.sort()
            if sel and n_sel: return min(res1, res2)
            elif sel: return res1
            else: return res2
        
        return trace(0,-1,4, mx)
    

if __name__ == "__main__":
    print(Solution().maximumWeight4([[18,23,48],[1,19,11],[16,19,37],[3,18,25],[6,22,44],[18,21,27],[3,21,29],[6,20,29],[3,24,38],[3,5,44]]))