from functools import cache

# 动态规划 - 分组背包
class Solution:
    def numRollsToTarget(self, n: int, k: int, target: int) -> int:
        # 使用动态规划，选或不选，!!不超时!!
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, j:int):
            if j < 0: return 0
            if i == 0: return (j==0) # 次数+1
            res = 0
            for x in range(1, k+1):
                res += dfs(i-1, j-x)
            return res % MOD
        
        return dfs(n, target)