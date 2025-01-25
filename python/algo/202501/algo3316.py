from cmath import inf
from functools import cache
from typing import List

# 双周赛 141
class Solution:
    def maxRemovals(self, source: str, pattern: str, targetIndices: List[int]) -> int:
        
        indices = set(targetIndices)

        @cache
        def dfs(i:int, j:int):
            if i < j : return -inf
            if i < 0: return 0

            cnt = dfs(i-1, j) + (1 if i in indices else 0)
            if j>=0 and source[i] == pattern[j]: cnt = max(cnt, dfs(i-1,j-1))
            return cnt
        
        return dfs(len(source)-1, len(pattern)-1)
        