import math
from typing import List


class Solution:
    def maximumSegmentSum(self, nums: List[int], removeQueries: List[int]) -> List[int]:
        n = len(nums)

        tree =  [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)
        tp = [0] * (2 ** (math.ceil(math.log(n, 2))+1) - 1)

        def pushdown(s, t, p):
            if s == t:
                tree[p] = tp[p]
            else:
                tree[p*2+1] += tp[p]
                tree[p*2+2] += tp[p]
                tp[p*2+1], tp[p*2+2] = tp[p], tp[p]
            tp[p] = 0

        def update(l:int, r:int, value:int, s:int, t:int, p:int):
            if l <= s and t <= r:
                tree[p] = value
                tp[p] = value
                return
            m = s + ((t - s) >> 1)
            if tp[p] and s != t:
                pushdown(s, t, p)
            if l <= m:
                update(l, r, value, s, m, p*2+1)
            if r > m:
                update(l, r, value, m + 1, t, p*2+2)
            tree[p] = tree[p*2+1]+tree[p*2+2]
        
        def query(l, r, s, t, p):
            if tp[p]:
                pushdown(s, t, p)
            # [l, r] 为查询区间, [s, t] 为当前节点包含的区间, p为当前节点的编号
            if l <= s and t <= r:
                return tree[p]
            m = s + ((t - s) >> 1)
            sumv = 0
            if l <= m:
                sumv = query(l, r, s, m, p * 2 + 1)
            if r > m:
                sumv += query(l, r, m + 1, t, p * 2 + 2)
            return sumv

        for i, v in enumerate(nums):
            update(i, i, v, 0, n-1, 0)
        
        ans = []
        for r in removeQueries:
            update(r, r, 0, 0, n-1, 0)
            res = query(r-1,r-1, 0, n-1, 0) if r-1 >= 0 else 0
            res = max(res, query(r+1,r+1, 0, n-1, 0) if r+1 < n else 0)
            ans.append(res)
        return ans

