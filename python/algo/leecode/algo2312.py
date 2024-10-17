from functools import cache

# 周赛 298
class Solution:
    def sellingWood(self, m: int, n: int, prices) -> int:
        def sellingWood(m:int, n:int):
            if dp[m-1][n-1] != -1: return dp[m-1][n-1]
            maxPrice = 0
            if (m,n) in priceMap.keys():
                maxPrice = max(maxPrice, priceMap[(m,n)])
            
            for i in range(0, m // 2):
                maxPrice = max(maxPrice, sellingWood(m-i-1, n) + sellingWood(i+1, n))
            
            for i in range(0, n // 2):
                maxPrice = max(maxPrice, sellingWood(m, n-i-1) + sellingWood(m, i+1)) 

            dp[m-1][n-1] = maxPrice
            return dp[m-1][n-1]

        dp = [[-1] * (n) for _ in range(m)]

        priceMap = {}
        for item in prices:
            priceMap[(item[0],item[1])] = item[2]
 
        if (1,1) in priceMap.keys():
            dp[0][0] = priceMap[(1,1)]
        else:
            dp[0][0] = 0

        return sellingWood(m, n)
    
    def sellingWood2(self, m: int, n: int, prices) -> int:

        @cache
        def dfs(h:int, w:int) -> int:
            if h == 1 and w == 1:
                return pr[h][w]

            res = pr[h][w]
            # 优化 range(1, w) -> range(1, w//2 + 1)
            for k in range(1, w//2 + 1):
                cur = dfs(h, k) + dfs(h, w-k)
                if cur > res: res = cur
            # 优化 range(1, h) -> range(1, h//2 + 1)
            for k in range(1, h//2 + 1):
                cur = dfs(k, w) + dfs(h-k, w)
                if cur > res: res = cur

            return res

        pr = [[0] * (n+1) for _ in range(m+1)]
        for h, w, p in prices:
            pr[h][w] = p

        return dfs(m, n)


    def sellingWood3(self, m: int, n: int, prices) -> int:
        # 递归 -> 递推
        dp = [[0] * (n+1) for _ in range(m+1)]
        for h, w, p in prices:
            dp[h][w] = p
        
        for i in range(1, m+1):
            for j in range(1, n+1):
                # 优化 range(1, j) - > range(1, j//2 +1) 
                dp[i][j] = max([dp[i][j]]+[dp[i][k] + dp[i][j-k] for k in range(1, j//2 +1)])
                # 优化 range(1, i) - > range(1, i//2 +1)
                dp[i][j] = max([dp[i][j]]+[dp[k][j] + dp[i-k][j] for k in range(1, i//2 +1)])
        return dp[m][n]
    
if __name__ == "__main__":
    sol = Solution()
    m, n, prices = 3, 5, [[1,4,2],[2,2,7],[2,1,3]]
    m, n, prices = 8, 2, [[5,2,9],[6,1,30]]
    print(sol.sellingWood(m, n, prices))
    print(sol.sellingWood2(m, n, prices))
    print(sol.sellingWood3(m, n, prices))

