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
            if i == n:
                if p+1 <= i <= p*2:return 0
                else: return prices[i-1]
            
            res = inf
            if p+1 <= i <=p*2 :
                res = min(res, dfs(i+1, p)) # 不选
                res = min(res, prices[i-1] + dfs(i+1, i)) # 选
            else:
                res = min(res, prices[i-1] + dfs(i+1, i)) # 必须选
            
            return res
    
        return dfs(1,0)

if __name__ == "__main__":
    sol = Solution()
    prices = [3,1,2]
    print(sol.minimumCoins(prices))    