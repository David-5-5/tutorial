from math import inf
from typing import List

# 周赛 369
class Solution:
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        # mx1, mn1, mx2, mn2 = 0, 0, 0, 0
        # for v in nums1:
        #     if v == 0:
        #         mx1 = inf
        #         mn1 += 1
        #     else:
        #         mx1 += v
        #         mn1 += v
        # for v in nums2:
        #     if v == 0:
        #         mx2 = inf
        #         mn2 += 1
        #     else:
        #         mx2 += v
        #         mn2 += v
        mn1 = mx1 = sum(nums1)
        mn2 = mx2 = sum(nums2)
        cnt1, cnt2 = nums1.count(0), nums2.count(0)
        if cnt1:
            mn1 += cnt1
            mx1 = inf
        if cnt2:
            mn2 += cnt2
            mx2 = inf
        if mx1 == inf and mx2 == inf: return max(mn1, mn2)
        if mn1 > mx2 or mn2 > mx1: return -1
        else: 
            return min(max(mn1, mn2), min(mx1, mx2))

if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [0,17,20,17,5,0,14,19,7,8,16,18,6], [21,1,27,19,2,2,24,21,16,1,13,27,8,5,3,11,13,7,29,7]
    print(sol.minSum(nums1, nums2))