# 周赛 301 
from functools import cache


class Solution:
    def idealArrays(self, n: int, maxValue: int) -> int:
        MOD = 10 ** 9 + 7
        # 自行解答，数位DP

        @cache
        def f(i: int, prev: int) -> int:
            if i == n and prev == maxValue: return 1
            
            res = 0
            if i == 0:
                for j in range(1, maxValue+1):
                    res += f(i+1, j)
            else:
                for j in range(1, (maxValue // prev)+1):
                    res += f(i+1, prev*j)
            
            return res % MOD
        
        return f(0, -1)
    

if __name__ == "__main__":
    sol = Solution()
    print(sol.idealArrays(5878,2900))