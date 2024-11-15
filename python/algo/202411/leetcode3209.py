from bisect import bisect_left, bisect_right
from cmath import inf
from typing import List

# 双周赛 134
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        # 参考题解 logTrick + 二分
        ans = 0
        for i, v in enumerate(nums):

            for j in range(i-1, -1, -1):
                if nums[j] == nums[j] & v:
                    break
                nums[j] &= v
            l = bisect_left(nums, k, 0, i+1)
            r = bisect_right(nums, k, 0, i+1)
            ans += r - l 
        return ans



if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,9,9,7,4], 1
    print(sol.countSubarrays(nums, k))