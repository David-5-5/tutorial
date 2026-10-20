from collections import defaultdict
from math import inf
from typing import List


class Solution:
    def minChanges(self, nums: List[int], k: int) -> int:
        mx = 1 << max(nums).bit_length()
        n = len(nums)
        sz = n // k
        count = [defaultdict(int) for _ in range(k)]
        for i, v in enumerate(nums):
            count[i % k][v] += 1

        def size(i: int) -> int:
            return sz + 1 if i < n % k else sz

        dp = [inf] * mx
        dp[0] = 0
        for i in range(k):
            g = [inf] * mx
            min_dp = min(dp)
            for mask in range(mx):
                if dp[mask] == inf: continue
                for x in count[i].keys():
                    g[mask^x] = min(g[mask^x], size(i) + dp[mask] - count[i][x])
                # for x in count[i].keys():
                #     g[mask] = min(g[mask], size(i) + dp[mask^x])
                # 优化为
            for mask in range(mx):
                g[mask] = min(g[mask], size(i) + min_dp)
            dp = g
        return dp[0]

if __name__ == "__main__":  
    print(Solution().minChanges2([3,4,5,2,1,7,3,4,7], 3))