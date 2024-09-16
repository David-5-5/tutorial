from functools import cache

# 周赛 299 
class Solution:
    def countHousePlacements2(self, n: int) -> int:
        # 自行解答 记忆化搜索 选或不选
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, prev:bool)->int:
            if i == n:return 1

            res = dfs(i+1, False) # 不选
            if prev == False: res += dfs(i+1, True) # 选

            return res % MOD
        
        res = dfs(0, False)
        return  res * res % MOD

    def countHousePlacements(self, n: int) -> int:
        # 自行解答 递推 动态规划
        MOD = 10 ** 9 + 7
        
        dp = [[0, 0] for _ in range(n+1)]
        dp[n] = [1,1]
        for i in range(n-1, -1, -1):
            
            dp[i][0] = (dp[i+1][0] + dp[i+1][1]) % MOD
            dp[i][1] = dp[i+1][0]

        return  (dp[0][0]) * (dp[0][0]) % MOD
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.countHousePlacements2(100))
    print(sol.countHousePlacements(100))
    print(sol.countHousePlacements(1000))