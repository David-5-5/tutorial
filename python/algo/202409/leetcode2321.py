from typing import List

# 周赛 299
class Solution:
    def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答
        mx1 = mx2 = d1 = d2 = 0
        for n1, n2 in zip(nums1, nums2):
            d1 += n2 - n1 # 计算 nums2 与 nums1 的差，最大值加到 sum(nums1)中
            if d1 < 0: d1 = 0 # 出现 0 重新开始计算，!!这是关键，隐式的滑动窗口!!
            elif d1 > mx1: mx1 = d1 # 计算 nums2 大于 nums1 连续元素的最大值

            # 逻辑同上
            d2 += n1 - n2 
            if d2 < 0: d2 = 0
            elif d2 > mx2: mx2 = d2
        
        # 返回两者的最大值
        return max(sum(nums1)+mx1, sum(nums2)+mx2)    