from cmath import inf
from functools import cache
from typing import List


class Solution:
    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        dep = [0] * n

        for u, v in edges:
            dep[v] |= 1 << u
        
        if len(edges) == 0:
            score.sort()
            res = 0
            for i, v in enumerate(score, 1):
                res += i * v
            return res

        @cache
        def next(state: int) -> int:
            ns = 0
            for i in range(n):
                if state & 1 << i: continue
                if state & dep[i] == dep[i]:
                    ns |= 1 << i
            return ns

        @cache
        def dfs(state: int) -> int:
            
            if state.bit_count() == n: return 0
            ns = next(state)
            res = 0
            for i in range(n):
                if ns & 1 << i:
                    res = max(res, dfs(state | 1<< i) + (state.bit_count() + 1) * score[i])
            return res

        return dfs(0)

    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        dep = [0] * n

        for u, v in edges:
            dep[v] |= 1 << u
        
        if len(edges) == 0:
            score.sort()
            res = 0
            for i, v in enumerate(score, 1):
                res += i * v
            return res

        @cache
        def dfs(state: int) -> int:
            
            if state.bit_count() == n: return 0
            res = 0
            for i, pre in enumerate(dep):
                if state & 1 << i: continue
                if state & pre == pre:
                    res = max(res, dfs(state | 1<< i) + (state.bit_count() + 1) * score[i])
            return res

        return dfs(0)