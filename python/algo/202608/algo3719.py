from collections import defaultdict
from typing import List

class Solution:

    def longestBalanced(self, nums: List[int]) -> int:
        # 暴力 O(N^2) 本题 N = 1500，但 3721 N = 10^5
        ans = 0
        for i, v in enumerate(nums):
            vis = set()
            cnt = [0, 0]
            for j in range(i, -1, -1):
                if nums[j] not in vis:
                    vis.add(nums[j])
                    cnt[nums[j] % 2] += 1
                if cnt[0] == cnt[1]:
                    ans = max(ans, i - j + 1)

        return ans

    def longestBalanced(self, nums: List[int]) -> int:
        # 
        idxs = [{}, {}]
        vis, ans = set(), 0
        idxs[0][0], idxs[1][0] = -1, -1

        for i, v in enumerate(nums):
            is_odd = v % 2
            if v not in vis:
                vis.add(v)
                idxs[is_odd][len(idxs[is_odd])] = i
            
            cur_l, opp_l = len(idxs[is_odd]), len(idxs[1^is_odd])

            if cur_l >= opp_l:
                ans = max(ans, i - idxs[is_odd][cur_l-opp_l])
            else:
                ans = max(ans, i-idxs[1^is_odd][opp_l-cur_l])
        
        return ans
