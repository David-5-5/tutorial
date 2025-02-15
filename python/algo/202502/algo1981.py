from functools import cache
from math import inf
from typing import List


class Solution:
    def minimizeTheDifference(self, mat: List[List[int]], target: int) -> int:
        
        ans = inf
        @cache
        def dfs(i:int, sum: int):
            nonlocal ans
            if i < 0: 
                ans = min(ans, abs(sum-target))
                return
            
            if sum - target > ans: return # 剪枝
            
            for v in mat[i]:
                dfs(i-1, v+sum)
        
        dfs(len(mat)-1, 0)
        return ans