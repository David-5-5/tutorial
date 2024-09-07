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

    # 以下参考题解 从记忆化搜索->递推->单调栈优化
    def minimumCoins4(self, prices: List[int]) -> int:
        # 自行解答 记忆化搜索
        n = len(prices)

        # 表示购买 i 后及其后面所有水果的最小值
        @cache
        def dfs(i:int) -> int:
            # if i > n: return 0
            if i*2 >=n : return prices[i-1] # 边界优化
            
            res = inf
            # [i,i*2] 可以是免费的，从 i*2+1 是不免费的
            for j in range(i+1, i*2+2):
                res = min(res, dfs(j)) # 逻辑[i,i*2]有更小的值，可以替换 i*2+1
            return res + prices[i-1]
        
        # 从 1 开始
        return dfs(1)

        # 自行解答 记忆化搜索
        

    def minimumCoins5(self, prices: List[int]) -> int:
        n = len(prices)
        # 递推  倒序
        dp = [prices[i-1] if i * 2 >= n else inf for i in range(n+1)]

        for i in range(n, 0, -1):
            if i*2 >=n:
                dp[i] = prices[i-1]
            else:
                # for j in range(i+1, min(i*2+2,n+1))
                #     dp[i] = min(dp[i], dp[j]) 
                dp[i] = prices[i-1] + min(dp[i+1:2*i+2])
        
        # 从 1 开始
        return dp[1]


    def minimumCoins6(self, prices: List[int]) -> int:
        # 滑动窗口

        
        return 


if __name__ == "__main__":
    sol = Solution()
    prices = [3,1,2]
    print(sol.minimumCoins(prices))
    print(sol.minimumCoins5(prices)) 