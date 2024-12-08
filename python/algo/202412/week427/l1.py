from typing import List


class Solution:
    def constructTransformedArray(self, nums: List[int]) -> List[int]:
        n = len(nums)
        result = [0] * n
        for i, v in enumerate(nums):
            # if v > 0:
            n_i = (v + i) % n
            # else:
            #     n_i = (v + i + n) % n
            result[i] = nums[n_i]
        return result
if __name__ == "__main__":
    sol = Solution()
    print(sol)