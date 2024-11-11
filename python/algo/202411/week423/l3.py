from collections import defaultdict
from typing import List


class Solution:
    def sumOfGoodSubsequences(self, nums: List[int]) -> int:
        # 自行解答 
        MOD = 10 ** 9 + 7
        dp = defaultdict(lambda: [0,0])
        ans = 0

        for v in nums:
            ss, cnt = 0, 1 # 本身
            for k in [v-1, v+1]:
                if k in dp.keys():
                    ss += dp[k][0]
                    cnt += dp[k][1]
            cur_sum = ss + cnt * v
            ans = (ans + cur_sum) % MOD
            dp[v][1] += cnt
            dp[v][0] += cur_sum

        return ans % MOD


if __name__ == "__main__":
    sol = Solution()
    nums = [8,4,5]
    print(sol.sumOfGoodSubsequences(nums))