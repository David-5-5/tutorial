from math import gcd
from typing import List

# 周赛 316
class Solution:
    def subarrayGCD(self, nums: List[int], k: int) -> int:
        n, ans = len(nums), 0
        for i in range(n):
            GCD = nums[i]
            for j in range(i, n):
                GCD = gcd(GCD, nums[j])
                if k > GCD : break
                if k == GCD:ans += 1

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [9,3,1,2,6,3], 3
    print(sol.subarrayGCD(nums, k))