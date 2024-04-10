from typing import List
from itertools import accumulate
class Solution:
    def stoneGameIII(self, stoneValue: List[int]) -> str:
        n = len(stoneValue)
        # dp 表示还剩下第 i,i+1,⋯ ,n−1 堆石子时，当前玩家最多能从剩下的石子中拿到的石子数目
        # 因此：
        # 1) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+1]
        #    当前玩家拿到 sum(i..n-1) - dp[i+1]
        # 2) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+2]
        #    当前玩家拿到 sum(i..n-1) - dp[i+1]
        # 3) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+3]
        #    当前玩家拿到 sum(i..n-1) - dp[i+1]
        # 综上所述：
        #    dp[i] = max(sum(i..n-1)-f[j]) = sum(i..n-1) - min(f[j])， j ∈ [i+1, i+3]
        dp = [0] * n + [0]

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

    def stoneGameIII2(self, stoneValue: List[int]) -> str:
        n = len(stoneValue)
        # dp 表示还剩下第 i,i+1,⋯ ,n−1 堆石子时，当前玩家最多比下一玩家多拿的数量
        # 因此：
        # 1) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+1]
        #    当前玩家拿到 sum(i..i) - dp[i+1]
        # 2) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+2]
        #    当前玩家拿到 sum(i..i+1) - dp[i+2]
        # 3) 当前玩家选择了一堆石子，那么留给下一位玩家的状态为 dp[i+3]
        #    当前玩家拿到 sum(i..i+2) - dp[i+3]
        # 综上所述：
        #    dp[i] = max(sum(i..i+j-1)-dp[i+j]) j ∈ [1, 3]
        dp = [-float("inf")] * n + [0]

        presum = list(accumulate(stoneValue, initial=0))

        for i in range(n-1, -1, -1):
            for j in range(i+1, i+4):
                if j < n+1:
                    dp[i] = max(presum[j]-presum[i]-dp[j], dp[i])
        
        if dp[0] > 0:
            return 'Alice'
        elif dp[0] == 0:
            return 'Tie'
        else:
            return 'Bob'


if __name__ == "__main__":
    sol = Solution()
    values = [1,2,3,7]
    print(sol.stoneGameIII2(values))