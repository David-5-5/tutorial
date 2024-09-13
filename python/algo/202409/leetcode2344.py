import math
from typing import List

# 周赛 302
class Solution:
    def minOperations(self, nums: List[int], numsDivide: List[int]) -> int:
        # 自行解答
        nums.sort()
        gcd = math.gcd(*numsDivide)
        for i in range(len(nums)):
            if gcd % nums[i] == 0:return i
        return -1


if __name__ == "__main__":
    sol = Solution()
    nums, numsDivide = [2,3,2,4,3], [9,6,9,3,15]
    nums, numsDivide = [3,2,6,2,35,5,35,2,5,8,7,3,4], [105,70,70,175,105,105,105]
    print(sol.minOperations(nums, numsDivide))
