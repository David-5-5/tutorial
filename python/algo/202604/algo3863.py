from itertools import pairwise

# 五、思维题 - 5.7 分类讨论
class Solution:
    def minOperations(self, s: str) -> int:
        if all(x <= y for x, y in pairwise(s)): return 0
        
        if (len(s) == 2): return -1

        mn, mx = min(s), max(s)

        if s[0] == mn or s[-1] == mx: return 1

        if any(ch == mn or ch == mx for ch in s[1:-1]): return 2

        return 3
