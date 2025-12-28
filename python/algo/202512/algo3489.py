from cmath import inf
from functools import cache
from typing import List

# 动态规划 - 三、背包 3.1 0-1 背包 进阶
class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        # 自行解答 记忆化搜索
        n = len(nums)

        cands = [[] for _ in range(n)]
        for inx, (l, r, v) in enumerate(queries):
            for i in range(l, r+1): cands[i].append((v, inx))

        ans = 0
        for i, (val, cand) in enumerate(zip(nums, cands)):
            m = len(cand)
            @cache
            def dfs(j: int, s: int) -> int:
                if s == 0: return cand[j-1][1]+1
                if j == m: return inf

                res = dfs(j+1, s)    # 不选
                if cand[j][0] <= s: res = min(res, dfs(j+1, s-cand[j][0]))
                
                return res
            if val == 0: continue
            ans = max(ans, dfs(0, val))

        return ans if ans < inf else -1
    
