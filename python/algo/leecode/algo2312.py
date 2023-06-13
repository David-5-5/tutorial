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

if __name__ == "__main__":
    sol = Solution()
    prices = [[1,1,10]]
    print(sol.sellingWood(1, 1 ,prices))
