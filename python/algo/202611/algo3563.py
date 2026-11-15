from functools import cache


class Solution:
    def lexicographicallySmallestString(self, s: str) -> str:
        # 参考题解 线性DP + 区间 DP
        isMatch = lambda x, y: abs(ord(x) - ord(y)) in (1, 25)
      
        n  = len(s)
        @cache
        def canEliminate(i:int, j:int) ->bool:
            # 区间 DP
            if i > j: return True

            if isMatch(s[i], s[j]) and canEliminate(i+1, j-1): return True
            for k in range(i+1, j-1, 2):
                if canEliminate(i, k) and canEliminate(k+1, j): return True
            return False
            
        @cache
        def dfs(i: int) -> str:
            # 线性DP
            if i == n: return ""
            res = s[i] + dfs(i+1)
            for j in range(i+1, n, 2):
                if canEliminate(i, j):
                    res = min(res, dfs(j+1))
            return res

        return dfs(0)