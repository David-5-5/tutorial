from bisect import bisect_right
from itertools import accumulate
import math
from typing import Counter, List

class Solution:
    # Refer to https://leetcode.cn/circle/discuss/CaOJ45/
    # https://leetcode.cn/problems/minimum-operations-to-form-subsequence-with-target-sum/solutions/2413344/tan-xin-by-endlesscheng-immn/
    def minOperations(self, nums: List[int], target: int) -> int:
        if sum(nums) < target:return -1

        cnt = Counter(nums)
        ans = s = i = 0
        while 1 << i <= target:
            s += cnt[1<<i] << i
            mask = (1<<(i+1)) - 1
            i += 1
            if s >= target & mask:
                continue

            ans += 1
            while cnt[1<<i] == 0:
                i += 1
                ans += 1

        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.minOperations([1,32,1,2],12))
