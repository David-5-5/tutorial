from functools import cache
from heapq import heapify, heappop

# 动态规化 - 其他
class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        # 自行解答
        weights = []        

        @cache
        def dfs(v: int) -> int:
            if v == 1: return 0

            if v % 2:
                return 1 + dfs(v *3 + 1)
            else: return 1 + dfs(v // 2)
        
        for i in range(lo, hi+1):
            weights.append((dfs(i), i))
        heapify(weights)
        for i in range(k-1):
            heappop(weights)
        return heappop(weights)[1]