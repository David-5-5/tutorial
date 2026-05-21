from bisect import bisect_right
from cmath import inf
from functools import cache
from typing import List


class Solution:
    def minMergeCost(self, lists: List[List[int]]) -> int:
        n = len(lists)

        @cache
        def length(i: int) -> int:
            res = 0
            for j in range(n):
                if (i >> j) & 1: res += len(lists[j])
            return res

        @cache
        def median(i: int) -> int:
            cnt = (length(i) + 1) // 2

            l, r = inf, -inf
            for j in range(n):
                if (i >> j) & 1:
                    l = min(l, min(lists[j]))
                    r = max(r, max(lists[j]))
            l -= 1
            r += 1
            while l + 1 < r:
                res = 0
                mid = (l + r) // 2
                for j in range(n):
                    if (i >> j) & 1: res += bisect_right(lists[j], mid)
                if res >= cnt: r = mid
                else : l = mid
            med = -inf
            for j in range(n):
                if (i >> j) & 1: 
                    inx = bisect_right(lists[j], r) # r is result
                    if inx: med = max(med, lists[j][inx-1])
            return med  


        @cache
        def dfs(st: int) -> int:
            if st.bit_count() == 1: return 0
            
            i = (st - 1) & st
            ans = inf
            while i > st//2:
                ans = min(ans, dfs(i) + dfs(st - i) + length(st) + abs(median(st - i) - median(i)))
                i = (i-1) & st
            return ans

        return dfs((1 << n) -1)