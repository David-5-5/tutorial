from math import inf
from typing import List

# 周赛 370
class Solution:
    def maxBalancedSubsequenceSum(self, nums: List[int]) -> int:
        n = len(nums)
        ans = res = -inf
        st = []
        for i, v in enumerate(nums[::-1]):
            if v <= 0:
                if v > res: res = v
                continue
            while st and st[-1] - (n-i-1) > nums[st[-1]]-v:
                res -= nums[st.pop()]
            if res < 0: res = 0 # 初始化
            st.append(n-i-1)
            res += v
            ans = max(res, ans)

        return max(ans,res)