from bisect import bisect_left, bisect_right
from typing import List


class Solution:
    def canMakePalindromeQueries(self, s: str, queries: List[List[int]]) -> List[bool]:
        n, m = len(s), len(queries)
        if sorted(s[0:n//2]) != sorted(s[n//2:]):
            return [False] * m

        sl = list(s[0:n//2])
        intervals = []
        for i in range(n//2):
            if sl[i] != s[n-i-1]:
                j = sl.index(s[n-i-1],i)
                sl[j] = sl[i]
                sl[i] = s[n-i-1]
                intervals.append([i,j])
        
        merge = []
        left, right = intervals[0]
        for l, r in intervals[1:]:
            if l > right:
                merge.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        merge.append([left, right])

        ans = []
        for a, b, c, d in queries:
            c, d = n - 1 - d, n - 1 - c

            ans.append(all((a<=l and r<=b) or (c<=l and r<=d)for l, r in merge))
            
        return ans