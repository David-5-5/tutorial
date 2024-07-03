from itertools import pairwise
from typing import List

class Solution:
    # 使用异或差分
    def minKBitFlips(self, nums: List[int], k: int) -> int:
        n = len(nums)
        diff = [0] * n
        diff[0] = nums[0]

        for i, (n0,n1) in enumerate(pairwise(nums)):
            # 亦或差分
            diff[i+1] = 1 - (n1^n0)
        ans = 0
        for i, d in enumerate(diff):
            if d == 1:
                continue
            if d != 1 and i + k > n:
                return -1
            # 异或 1, 实现位翻转
            diff[i] ^= 1
            if i + k < n:
                diff[i+k] ^= 1
            ans += 1
        return ans


if __name__ == "__main__":
    sol = Solution()
    print(sol.minKBitFlips([0,1,1,0], 2))