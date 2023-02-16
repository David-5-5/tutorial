class Solution:
    def minimumWhiteTiles(self, floor: str, numCarpets: int, carpetLen: int) -> int:
        n = len(floor)
        if numCarpets * carpetLen >= n: return 0
        dp = [[0] * numCarpets for _ in range(n)]
        for i in range(n):
            dp[i][0] = floor[i] + dp[i-1][0] if i else 0
        
        

        return dp[n-1][numCarpets-1]