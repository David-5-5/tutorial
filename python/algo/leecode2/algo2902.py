from typing import List
from collections import Counter
class Solution:
    def countSubMultisets(self, nums: List[int], l: int, r: int) -> int:
        MOD = 10 ** 9 + 7
        iter = Counter(nums)
        n = len(iter)
        dp = [[0]* (r+1) for _ in range(n+1)]
        dp[0][0] = 1
        for i, val in enumerate(iter):
            for j in range(0, r+1):
                for k in range(iter[val]+1):
                    if j-k*val >= 0:
                        dp[i+1][j] += dp[i][j-k*val] % MOD
        
        return sum(dp[-1][l:]) % MOD

    def countSubMultisets2(self, nums: List[int], l: int, r: int) -> int:
        MOD = 10 ** 9 + 7
        cnt = Counter(nums)
        # n = len(cnt)
        n = len(cnt) - (0 in cnt)
        dp = [[0]* (r+1) for _ in range(n+1)]
        dp[0][0] = cnt[0] + 1
        cnt[0] + 1
        del cnt[0]

        for i, val in enumerate(cnt):
            for j in range(0, r+1):
                dp[i+1][j] = (dp[i+1][j-val] if j-val>=0 else 0) + \
                              dp[i][j] - \
                              (dp[i][j-(cnt[val]+1)*val] if j-(cnt[val]+1)*val>=0 else 0)

        return sum(dp[-1][l:]) % MOD

if __name__ == "__main__":
    sol = Solution()
    nums, l, r = [1,2,2,3], 6, 6
    nums, l, r = [2,1,4,2,7], 1, 5
    nums, l, r = [1,2,1,3,5,2], 3, 5
    nums, l, r = [0,0,1,2,3], 2, 3
    print(sol.countSubMultisets2(nums, l, r))