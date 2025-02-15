from typing import List
from collections import Counter

# 双周赛 115
class Solution:
    def countSubMultisets(self, nums: List[int], l: int, r: int) -> int:
        # 经典多重背包算法，超时
        MOD = 10 ** 9 + 7
        iter = Counter(nums)
        n = len(iter)
        dp = [[0]* (r+1) for _ in range(n+1)]
        dp[0][0] = 1
        for i, val in enumerate(iter):
            for j in range(0, r+1):
                for k in range(iter[val]+1):
                    if j-k*val < 0:
                        break
                    dp[i+1][j] += dp[i][j-k*val] % MOD
        
        return sum(dp[-1][l:]) % MOD

    def countSubMultisets2(self, nums: List[int], l: int, r: int) -> int:
        # 滚动数组优化
        # dp[i+1][j] = dp[i][j] + dp[i][j-x] + ... + dp[i][j-k*x]
        # dp[i+1][j-x] = dp[i][j-x] + dp[i][j-2*x] ... + dp[i][j-k*x] + dp[i][j-(k+1)*x]
        # 综合上面两式得出
        # dp[i+1][j] = dp[i+1][j-x] + dp[i][j-x] - dp[i][j-(k+1)*x]
        # 无需对 k 进行遍历，修改上面方案如下
        MOD = 10 ** 9 + 7
        cnt = Counter(nums)

        n = len(cnt) - (0 in cnt)
        dp = [[0]* (r+1) for _ in range(n+1)]
        dp[0][0] = cnt[0] + 1

        del cnt[0] # 删除 0，是由于当 val = 0 时，转移方程无效

        for i, val in enumerate(cnt):
            for j in range(0, r+1):
                dp[i+1][j] = (dp[i+1][j-val] if j-val>=0 else 0) + \
                              dp[i][j] - \
                              (dp[i][j-(cnt[val]+1)*val] if j-(cnt[val]+1)*val>=0 else 0)

        return sum(dp[-1][l:]) % MOD

    
if __name__ == "__main__":
    sol = Solution()
    nums, l, r = [1,2,2,3], 6, 6
    # nums, l, r = [2,1,4,2,7], 1, 5
    # nums, l, r = [1,2,1,3,5,2], 3, 5
    nums, l, r = [0,0,0,1,2,3], 2, 3
    print(sol.countSubMultisets(nums, l, r))
    print(sol.countSubMultisets3(nums, l, r))