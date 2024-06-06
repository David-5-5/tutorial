from  typing import List
from itertools import accumulate
class Solution:
    def maximumStrength(self, nums: List[int], k: int) -> int:
        n = len(nums)

        s = list(accumulate(nums, initial=0))
        dp = [[0] * (n+1) for _ in range(k+1)]
        for i in range(1, k+1):
            dp[i][i-1] = mx = - float("inf")
            for j in range(i, n+1):
                w = (1 if (i+1) % 2 == 0 else -1) * (k-i+1)
                mx = max(mx, dp[i-1][j-1] - s[j-1] * w)
                dp[i][j] = max(dp[i][j-1], s[j] * w + mx)
                
        return dp[k][n]

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,-1,2], 3
    print(sol.maximumStrength(nums, k))