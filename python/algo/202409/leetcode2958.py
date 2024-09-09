from collections import defaultdict
from typing import List

# 双周赛 119
class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        res = l = 0
        cnt = defaultdict(int)
        
        for r, num in enumerate(nums):
            cnt[num] += 1
            while cnt[num] > k:
                cnt[nums[l]] -= 1
                l += 1
            if r - l + 1 > res: res = r - l + 1
        return res


if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,1,2,3,1,2], 2
    print(sol.maxSubarrayLength(nums, k))