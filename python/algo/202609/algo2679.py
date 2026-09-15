from typing import List


class Solution:
    def matrixSum(self, nums: List[List[int]]) -> int:
        m, n, ans = len(nums), len(nums[0]), 0
        
        for i in range(m):
            nums[i].sort()

        for j in range(n):
            mx = 0
            for i in range(m):
                if nums[i][j] > mx: mx = nums[i][j]
            ans += mx
        return ans
