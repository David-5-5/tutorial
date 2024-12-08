from itertools import accumulate
from math import inf
from typing import List


class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        n = len(nums)
        presum = list(accumulate(nums, initial=0))
        i = 0
        ans = nums[0:k]
        while i < n:
            l = i
            for r in range(l + k, n+1, k):
                ans = max(ans, presum[r]-presum[l])
                if (presum[r] - presum[l]) < 0:
                    l = r
            i += 1

        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, k = [-1,-2,-3,-4,-5], 4
    print(sol.maxSubarraySum(nums, k))