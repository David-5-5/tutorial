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
    
    def minZeroArray2(self, nums: List[int], queries: List[List[int]]) -> int:
        # 参考题解 0-1 背包
        n = len(nums)

        ans = 0
        for i, capacity in enumerate(nums):
            if capacity == 0: continue
            
            dp = [True] + [False] * capacity
            for k, (l, r, v) in enumerate(queries):
                if l > i or i > r: continue # i ∉ [l, r]
                for j in range(capacity, v-1, -1):  # 容量倒序，降维
                    dp[j] = dp[j] or dp[j-v]
                if dp[capacity]:
                    ans = max(ans, k + 1)
                    break
            else: return -1 # 没有 break 返回 -1

        return ans