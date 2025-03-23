from functools import cache

# 动态规划 -  多维 DP
class Solution:
    def countWinningSequences(self, s: str) -> int:
        # 自行解答
        mod = 10 ** 9 + 7
        n = len(s)
        game = "FWE"

        def score(a, b) -> int: 
            if a == b: return 0
            if a == 'F' and b == 'E' or a =='W' and b == 'F' or a=='E' and b == 'W':
                return 1
            else: return -1
                
        @cache
        def dfs(i: int, t:int, p:int) -> int:
            if i<0: return 1 if t > 0 else 0
            
            if (t+i) < 0: return 0  # 剪枝

            res = 0
            for k in range(3):
                if k == p: continue
                res = (res + dfs(i-1, t + score(game[k], s[i]), k)) % mod
            return res
        return dfs(n-1, 0, -1)
