from math import factorial
from typing import List


class Solution:
    def minMaxSums(self, nums: List[int], k: int) -> int:
        MOD = 10 ** 9 + 7
        nums.sort()
        n = len(nums)
        ans = 0
        
        def count(i:int):
            res = 0
            c = n-i-1
            for j in range(1, k+1):
                if j > c:break
                res += factorial(c, j)
        
        for i, v in enumerate(nums):
            cnt = count(i)
            ans = (ans + (cnt * v)) % MOD

        
        for i, v in  enumerate(nums[::-1]):
            cnt = count(i)
            ans = (ans + (cnt * v)) % MOD

        return ans % MOD


if __name__ == "__main__":
    sol = Solution()
    print(sol)