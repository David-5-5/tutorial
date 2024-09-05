from functools import cache
from math import inf
from typing import List

# 双周赛 118
class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        # 自行解答 记忆化搜索
        n = len(prices)

        @cache
        def dfs(i:int, p:int) -> int:
            if i == n-1:
                if p+1 <= i+1 <= p*2:return 0
                else: return prices[i]
            
            res = inf
            if p+1 <= i+1 <=p*2 :
                res = min(res, dfs(i+1, p)) # 不选
                res = min(res, prices[i] + dfs(i+1, i+1)) # 选
            else:
                res = min(res, prices[i] + dfs(i+1, i+1)) # 必须选
            
            return res
    
        return dfs(0,0)

    def minimumCoins2(self, prices: List[int]) -> int:
        # 自行解答 记忆化搜索 改 DP
        n = len(prices)
        dp = [[inf] * n for _ in range(n)]
        
        for i in range(n-1,-1,-1):
            for j in range(n-1,-1,-1):
                if j+1 <= i+1 <=j*2 :
                    dp[i][j] = min(dp[i][j], dp[i+1][j] if i+1<n else 0)
                    dp[i][j] = min(dp[i][j], prices[i] + dp[i+1][i+1] if i+1<n else 0)
                else:
                    dp[i][j] = prices[i] + (dp[i+1][i+1] if i+1<n else 0)

        return dp[0][0]

    def minimumCoins3(self, prices: List[int]) -> int:
        # 自行解答 记忆化搜索 改 DP
        n = len(prices)
        dp = [inf] * n
        
        for i in range(n-1,-1,-1):
            for j in range(n):
                if j+1 <= i+1 <=j*2 :
                    dp[j] = min(dp[j], dp[j] if i+1<n else 0)
                    dp[j] = min(dp[j], prices[i] + dp[i+1] if i+1<n else 0)
                else:
                    dp[j] = prices[i] + (dp[i+1] if i+1<n else 0)

        return dp[0]

if __name__ == "__main__":
    sol = Solution()
    prices = [3,1,2]
    print(sol.minimumCoins(prices))
    print(sol.minimumCoins3(prices)) 