from cmath import inf
from collections import defaultdict
from itertools import accumulate
from typing import List

# 双周赛 123
class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        # 提示 前缀和 + 哈希，自行解答 
        presum = list(accumulate(nums, initial=0))
        
        # key: v, value: min(presum[i]), where i is index of v in nums
        # 求区间和的最大值:
        #   result = max(presum[j+1] - presum[i]),where abs(nums[j] - nums[i]) == k
        #   result = presum[j+1] - min(presum[i]), 因此相同的key保留最小的 presum[i]
        vsum = defaultdict(lambda:inf)
        
        ans = -inf
        for j, v in enumerate(nums):
            if ans < presum[j+1] - vsum[v-k]:
                ans = presum[j+1] - vsum[v-k]
            if ans < presum[j+1] - vsum[v+k]:
                ans = presum[j+1] - vsum[v+k]
            # 相同 
            if vsum[v] >  presum[j]: vsum[v] = presum[j]
        return 0 if ans == -inf else ans 

if __name__ == "__main__":
    sol = Solution()
    nums, k  = [-1,3,2,4,5], 3
    nums, k  = [5,3,3],2
    print(sol.maximumSubarraySum(nums,k))