from itertools import accumulate
from math import inf
from typing import List


class Solution:
    def maxSubarraySum(self, nums: List[int], k: int) -> int:
        # 参考题解 前缀和 + 最小前缀
        n = len(nums)
        presum = list(accumulate(nums, initial=0))
        mn_k = [inf] * k 
        ans = -inf

        for i in range(n+1):
            if presum[i]-mn_k[i%k] > ans : ans = presum[i]-mn_k[i%k]
            if presum[i] < mn_k[i%k] : mn_k[i%k] = presum[i]
        
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, k = [-1,-2,-3,-4,-5], 4
    print(sol.maxSubarraySum(nums, k))