from functools import cache

#  动态规划 -  区间 DP
class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        # 自行解答  记忆化搜索
        n = len(s)

        @cache
        def dfs(i:int, j:int, l:int) -> int:
            if i == j: return 1
            if i > j: return 0
            # 不选
            res = max(dfs(i+1, j, l), dfs(i, j-1, l))
            # 选
            if s[i] == s[j]: res = max(res, 2 + dfs(i+1, j-1, l))
            else:            
                x = min((ord(s[i]) - ord(s[j])) % 26, (ord(s[j]) - ord(s[i])) % 26)
                if x <= l: res = max(res, 2 + dfs(i+1, j-1, l-x))
            return res
        ans = dfs(0, n-1, k)
        dfs.cache_clear()
        return ans
                    
        