from typing import List


class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        result = [0] * n
        for i, v in enumerate(nums):
            n_i = (v + i) % n  # python 支持负数取模
            result[i] = nums[n_i]
        return result
    

if __name__ == "__main__":
    sol = Solution()
    print(sol.constructTransformedArray([3,-2,1,1]))