from typing import List

from itertools import accumulate
class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        n = len(piles)

        presum = list(accumulate(piles, initial=0))

        dp = [[0] * (n+1) for _ in range(n+1)]

        for i in range(n-1,-1,-1):
            for x in range(n):
                if x+1+i > n:
                    break;
                dp[i][x] = presum[n]-presum[i] - max(dp[i+x+1][0:(1+x)*2])

        return max(dp[0][0],dp[0][1])



if __name__ == "__main__":
    sol = Solution()
    piles = [77,12,64,35,28,4,87,21,20]
    print(sol.stoneGameII(piles))