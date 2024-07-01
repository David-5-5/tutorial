from itertools import accumulate
from typing import List


class Solution:
    def sumOfPower(self, nums: List[int]) -> int:
        MOD = 10 ** 9 + 7
        
        nums.sort()
        ss = list(accumulate(accumulate(nums), initial=0))

        hero = 0
        for i, num in enumerate(nums):
            hero = (hero + (num ** 3) + ss[i] * (num ** 2)) % MOD
        return hero

if __name__ == "__main__":
    sol = Solution()
    nums = [2,1,4,3]
    print(sol.sumOfPower(nums))