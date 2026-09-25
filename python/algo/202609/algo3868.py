from collections import defaultdict


class Solution:
    def minCost(self, nums1: list[int], nums2: list[int]) -> int:
        cnt1, cnt = defaultdict(int), defaultdict(int)
        for v1, v2 in zip(nums1, nums2):
            cnt[v1] += 1
            cnt[v2] += 1
            cnt1[v1] += 1
        
        ans = 0
        for k, v in cnt.items():
            if v % 2: return -1
            ans += abs(v//2 - cnt1[k])
        
        return ans // 2