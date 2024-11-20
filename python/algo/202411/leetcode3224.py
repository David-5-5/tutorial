from collections import Counter
from itertools import accumulate
from math import inf
from typing import List

# 双周赛 135
class Solution:
    def minChanges(self, nums: List[int], k: int) -> int:
        # 参考题解
        n = len(nums)
        diff = [abs(nums[i]-nums[n-i-1]) for i in range(n//2)]
        mx = [0] * (k+1)
        for i in range(n//2):
            p, q = min(nums[i],nums[n-1-i]), max(nums[i],nums[n-1-i])
            mx[max(q, k-p)] += 1
        sum2 = list(accumulate(mx, initial=0))
        cnt = Counter(diff)

        ans = inf
        for x in range(k+1):
            ans = min(ans, n // 2 - cnt[x] + sum2[x])
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [0,1,2,3,3,6,5,4], 6
    print(sol.minChanges(nums, k))
