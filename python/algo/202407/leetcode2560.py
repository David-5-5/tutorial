from bisect import bisect_left
from typing import List
# 周赛 331 二分查找，自行解答
class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        # left = min(nums) - 1
        right = max(nums) + 1

        def check(mn:int) -> int:
            # mn += 1
            prev, cnt = -2, 0
            for i, v in enumerate(nums):
                if v <= mn and i - 1 > prev:
                    cnt += 1
                    prev = i
                if cnt == k: return True
            return False

        return bisect_left(range(right), True, key=check)

if __name__ == "__main__":
    nums, k = [2,3,5,9], 2
    nums, k = [2,7,9,3,1], 2
    sol = Solution()
    print(sol.minCapability(nums, k))