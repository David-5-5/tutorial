from collections import defaultdict
from typing import List


class Solution:
    def arithmeticTriplets(self, nums: List[int], diff: int) -> int:
        cnt = defaultdict(int)
        ans = 0
        for num in nums:
            if cnt[num - diff] == 1 and cnt[num - 2*diff] == 1: ans += 1
            cnt[num] = 1
        return ans


if __name__ == "__main__":
    sol = Solution()
    nums, diff = [0,1,4,6,7,10], 3
    print(sol.arithmeticTriplets(nums, diff))