from itertools import accumulate
from math import inf
from typing import List
from sortedcontainers import SortedList

# 周赛 365
class Solution:
    def minSizeSubarray(self, nums: List[int], target: int) -> int:
        # 自行解答 前缀和
        n_sum = sum(nums)
        rem, div = target % n_sum, target // n_sum
        n = len(nums)

        # 连接两个nums数组求前缀和，兼容尾部和头部相连这种情况
        # nums[j..n] + nums[0:i] i < j
        presum = SortedList(accumulate(nums+nums, initial=0))

        ans = inf
        
        start = presum.bisect_right(rem)

        for r in range(start, 2*n+1):
            v = presum[r]
            if v == rem:
                if ans > r: ans = r
            else:
                l = presum.bisect_right(v-rem)
                if l > 0 and presum[l-1] == v-rem and ans > r-l+1:
                    ans = r-l+1

        return div * n + ans if ans < inf else -1

if __name__ == "__main__":
    sol = Solution()
    nums, target = [1,2,3], 5
    print(sol.minSizeSubarray(nums, target))
