from math import inf
from typing import List

# 周赛 369
class Solution:
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答 分类讨论
        mn1 = mx1 = sum(nums1)
        mn2 = mx2 = sum(nums2)
        cnt1, cnt2 = nums1.count(0), nums2.count(0)
        if cnt1:
            mn1 += cnt1
            mx1 = inf
        if cnt2:
            mn2 += cnt2
            mx2 = inf
        # if mx1 == inf and mx2 == inf: return max(mn1, mn2)
        if mn1 > mx2 or mn2 > mx1: return -1
        else: 
            return min(max(mn1, mn2), min(mx1, mx2))
        
    def minSum(self, nums1: List[int], nums2: List[int]) -> int:
        # 参考题解
        mn1 = sum(max(v, 1) for v in nums1)
        mn2 = sum(max(v, 1) for v in nums2)

        if( mn1 < mn2 and nums1.count(0) == 0) or (mn1 > mn2 and nums2.count(0) == 0):
            return -1
        else: return max(mn1, mn2)
        
if __name__ == "__main__":
    sol = Solution()
    nums1, nums2 = [0,17,20,17,5,0,14,19,7,8,16,18,6], [21,1,27,19,2,2,24,21,16,1,13,27,8,5,3,11,13,7,29,7]
    print(sol.minSum(nums1, nums2))