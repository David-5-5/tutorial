from typing import List
from functools import lru_cache

from itertools import accumulate
class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        n = len(piles)

        presum = list(accumulate(piles, initial=0))
        # 动态规划
        # dp[i][x] 表示 第 i 堆石子开始， 当前选手选择 x 堆石子 能获取的值
        # dp[i][x] = sum(piles[i..n-1]) - max(dp[i+x][1..max(x,m)*2])
        # 若不存在 m， i 可以从 n-1 开始，逐步求解到起始 0
        # 由于 m = max(m, x), 是从 i 从 0 开始计算的，因此采用递归的实现方式
        # 最终的结果为 max (dp[0][1], dp[0][2]) , m 初始值为 1
        @lru_cache(maxsize = None)
        def dp(begin: int, x: int, m: int):
            if begin + x >= n:
                return presum[n]-presum[begin]
            
            opp = 0
            for i in range(2*m):
                if begin+x+i+1 > n:
                    break;
                opp = max(opp, dp(begin+x, i+1, max(m, (i+1))))

            return presum[n]- presum[begin] - opp

        return max(dp(0,1,1),dp(0,2,2))



if __name__ == "__main__":
    sol = Solution()
    piles = [1,2,3,4,5,100]
    print(sol.stoneGameII(piles))