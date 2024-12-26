from itertools import accumulate
from typing import List

# 周赛 376 
class Solution:
    def maxFrequencyScore(self, nums: List[int], k: int) -> int:
        # 方法一，类似于 2602
        # 滑动窗口 排序后，一段连续的子数组修改成同一值具有最少的修改次数
        # 众数 - 中位数 - 将数组中的所有元素修改为中位数的次数最少
        n = len(nums)
        nums.sort()
        pres = list(accumulate(nums, initial= 0))
        
        def distance_sum(l:int, r:int) -> int:
            mid = (l + r) // 2
            # res = nums[mid] * (mid-l) - (pres[mid] - pres[l])
            # res += pres[r+1]-pres[mid+1] - nums[mid] * (r-mid)
            # return res
            # 合并上述上诉两式
            return pres[r+1] + pres[l] - pres[mid+1] - pres[mid] + nums[mid] * (2*mid-l-r)
        
        ans = l = 0
        for r in range(n):
            while distance_sum(l, r) > k:
                l += 1
            
            ans = max(ans, r - l + 1)

        return ans
