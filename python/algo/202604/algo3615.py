from functools import cache
from typing import List

# 九、状态压缩 DP（状压 DP） 9.2 排列型状压 DP ② 相邻相关
class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        # 自行解答 2463
        g = [[] for _ in range(n)]

        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        
        ans = 1
        @cache
        def dfs(u: int, v:int, state: int) :
            # 保持 u < v 减少状态
            nonlocal ans
            if state.bit_count() > ans: ans = state.bit_count()
            
            for x in g[u]:
                if (state >> x) & 1: continue
                for y in g[v]:
                    if x == y or (state >> y) & 1: continue
                    if label[x] == label[y]: dfs(min(x,y), max(x,y), state | 1<< x | 1 << y)
        
        for i in range(n):
            for x in g[i]:
                for y in g[i]:
                    if x == y or label[x] != label[y]: continue
                    dfs(min(x,y), max(x,y), 1 << i | 1 << x | 1<< y)
        
        for u in range(n):
            for v in g[u]:
                if u < v and label[u] == label[v]:
                    dfs(u, v, 1 << u | 1<< v)
        return ans
