from itertools import accumulate
from typing import List

# 3427
class Solution:
    def subarraySum(self, nums: List[int]) -> int:
        pres = list(accumulate(nums, initial=0))

        ans = 0
        for i, v in enumerate(nums):
            ans += pres[i+1] - pres[max(0, i-v)]
        return ans


if __name__ == "__main__":
    sol = Solution()
    print(sol)