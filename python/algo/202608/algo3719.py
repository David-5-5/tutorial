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

