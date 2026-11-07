from bisect import bisect_left
from collections import defaultdict
from typing import List


class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n, m = len(nums), len(queries)
        pos = defaultdict(list)

        for i, v in enumerate(nums):
            pos[v].append(i)
        
        ans = [-1] * m

        for i, idx in enumerate(queries):
            v = nums[idx]
            if len(pos[v]) == 1: continue

            p = bisect_left(pos[v], idx)
            if p == 0: ans[i] = n + pos[v][p] - pos[v][-1]
            else: ans[i] = pos[v][p] - pos[v][p-1]
            
            if p == len(pos[v]) - 1:
                ans[i] = min(ans[i], n + pos[v][0] - pos[v][p])
            else: ans[i] = min(ans[i], pos[v][p+1] - pos[v][p])
            
        return ans        