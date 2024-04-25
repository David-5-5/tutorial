from typing import List
from itertools import accumulate
class Solution:
    def stoneGameVII(self, stones: List[int]) -> int:
        n = len(stones)
        # 定义二维数组 dp，其行数和列数都等于石子的堆数，dp[i][j] 表示当剩下的石子堆为下标 i 到下标 j 时，
        # 即在下标范围[i,j]中，当前玩家与另一个玩家的石子数量之差的最大值
        # 状态转移方程即为
        # dp[i][j] 下列两种情况，取最大值
        # 1， 当前选择取左端石子，sum[i+1..j] - dp[i+1][j], 其中 dp[i+1][j] 下一选手最佳结果
        # 2， 当前选择取右端石子，sum[i..j-1] - dp[i][j-1], 其中 dp[i+1][j] 下一选手最佳结果
        # 初始值，当只有一个石子时，得分为 0， dp 初始都设为 0 
        # 时间复杂度为 O(n^2)
        presum = list(accumulate(stones, initial=0))  # 计算前缀和
        dp = [[0]* n for _ in range(n)]
        
        for j in range(1, n):
            for i in range(j-1, -1, -1):
                dp[i][j] = max(presum[j+1]-presum[i+1]-dp[i+1][j], presum[j] - presum[i] - dp[i][j-1])
        
        return dp[0][n-1]
    
if __name__ == "__main__":
    sol = Solution()
    stones = [5,3,1,4,2]
    print(sol.stoneGameVII(stones))