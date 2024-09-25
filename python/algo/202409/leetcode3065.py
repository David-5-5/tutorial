from bisect import bisect_left
from typing import List

# 双周赛 125
class Solution:
    def minOperations(self, nums: List[int], k: int) -> int:
        # 自行解答，运行时间 8033 ms
        nums.sort()
        ans = 0
        while nums[0] < k:
            a = nums.pop(0)
            b = nums.pop(0)
            nw = a * 2 + b
            inx = bisect_left(nums,nw)
            nums.insert(inx, nw)
            ans += 1

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, k = [2,11,10,1,3], 10
    print(sol.minOperations(nums, k))