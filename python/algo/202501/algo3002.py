from typing import List

# 周赛 379
class Solution:
    def maximumSetSize(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答
        n = len(nums1)

        nums1, nums2 = set(nums1), set(nums2)
        
        if len(nums1) < len(nums2): # nums1 为元素多的集合
            nums1, nums2 = nums2, nums1
        
        nums1 -= nums2 # nums1 集合中删除 nums2
        
        ans = min(len(nums1),n//2) + len(nums2)
        return ans if ans < n else n
