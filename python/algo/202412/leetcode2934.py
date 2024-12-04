from typing import List

# 周赛 371
class Solution:
    def minOperations(self, nums1: List[int], nums2: List[int]) -> int:
        # 自行解答，贪心。类似于 1007，多米诺，相等行的交换次数
        n = len(nums1)
        res1 = 0
        res2 = 1
        last1, last2 = nums1[-1], nums2[-1]
        for n1, n2 in zip(nums1[0:n-1], nums2[0:n-1]):
            if n1 <= last1 and n2 <= last2: continue
            if n1 <= last2 and n2 <= last1: res1 += 1
            else: return -1
        
        last1, last2 = last2, last1
        for n1, n2 in zip(nums1[0:n-1], nums2[0:n-1]):
            if n1 <= last1 and n2 <= last2: continue
            if n1 <= last2 and n2 <= last1: res2 += 1
        return min(res1, res2)