from typing import List
from itertools import accumulate
class Solution:
    def stoneGameIII(self, stoneValue: List[int]) -> str:
        n = len(stoneValue)
        dp = [0] * n + [0]
        # dp[-1] = stoneValue[-1]

        presum = list(accumulate(stoneValue, initial=0))

        for i in range(n-1, -1, -1):
            # dp[i+1:i+4] 取 i 后的三个元素
            dp[i] = presum[n]- presum[i] - min(dp[i+1:i+4])
        
        if 2 * dp[0] > presum[n]:
            return 'Alice'
        elif 2 * dp[0] == presum[n]:
            return 'Tie'
        else:
            return 'Bob'


if __name__ == "__main__":
    sol = Solution()
    values = [1,2,3,7]
    print(sol.stoneGameIII(values))