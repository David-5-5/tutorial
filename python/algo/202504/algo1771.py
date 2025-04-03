from functools import cache

# 动态规划 -  区间 DP
class Solution:
    def longestPalindrome(self, word1: str, word2: str) -> int:
        # 自行解答 比较粗暴，搞了两个记忆化搜索
        n, m = len(word1), len(word2)

        @cache
        def sub_dfs(w:int, i:int, j:int) -> int:
            if i == j:return 1
            if i > j:return 0

            res = max(sub_dfs(w, i+1, j), sub_dfs(w, i, j-1))
            if (w==1 and word1[i] == word1[j]):
                res = max(res, 2 + sub_dfs(w, i+1, j-1))

            if (w==2 and word2[i] == word2[j]):
                res = max(res, 2 + sub_dfs(w, i+1, j-1))

            return res

        @cache
        def dfs(i: int, j: int, match: bool) -> int:
            if i == n and j == -1: return 0
            if i == n or j == -1:
                if match:
                    if i == n: return sub_dfs(2, 0, j)
                    else: return sub_dfs(1, i, n-1)
                else: return 0
            
            res = max(dfs(i+1, j, match), dfs(i, j-1, match))
            if word1[i]  == word2[j]: res = max(res, 2 +dfs(i+1, j-1, True))

            return res

        ans = dfs(0, m-1, False)
        dfs.cache_clear()
        return ans
            
