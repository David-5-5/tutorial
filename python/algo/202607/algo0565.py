from typing import List


class Solution:
    def arrayNesting(self, nums: List[int]) -> int:
        ans, cnt, n = 0, 0, len(nums)
        vis = [False] * n
        for i in nums:
            ni = i
            while not vis[ni]:
                cnt += 1
                vis[ni] = True
                ni = nums[ni]
            if cnt > ans: ans = cnt
            cnt = 0
        return ans