from functools import cache

# 动态规划 -  其他区间 DP
class Solution:
    def getMoneyAmount(self, n: int) -> int:
        # 自行解答
        @cache
        def dfs(i:int, j:int) -> int:
            if i >= j: return 0     # 必须 >=

            res = n*n
            for k in range(i, j):   # 如果剩两个数，猜小的
                res = min(res, k + max(dfs(i,k-1), dfs(k+1, j)))
            
            return res
        
        return dfs(1, n)