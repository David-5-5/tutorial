from typing import List


class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)

        ans = []
        for i in range(1<<n):
            sub = []
            for j in range(n):
                if i >> j & 1: sub.append(nums[j])
            ans.append(sub)

        return ans