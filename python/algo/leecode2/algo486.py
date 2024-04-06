from typing import List
class Solution:
    def predictTheWinner(self, nums: List[int]) -> bool:
        n = len(nums)
        # 定义二维数组 dp，其行数和列数都等于石子的堆数，dp[i][j] 表示当剩下的石子堆为下标 i 到下标 j 时，
        # 即在下标范围[i,j]中，当前玩家与另一个玩家的石子数量之差的最大值
        dp = [[nums[i] if i==j else 0 for i in range(n)] for j in range(n)]

        for j in range(1, n):
            for i in range(j-1, -1, -1):
                dp[i][j] = max(nums[i]-dp[i+1][j], nums[j]-dp[i][j-1])
        
        if dp[0][n-1] >= 0: return True
        else: return False
    
if __name__ == "__main__":
    sol = Solution()
    nums = [1,5,233,7]
    print(sol.predictTheWinner(nums))
