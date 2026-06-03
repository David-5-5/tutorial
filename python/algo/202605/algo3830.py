from functools import cache
from typing import List

# // 六、状态机 DP - 6.3 进阶
class Solution:
    def longestAlternating(self, nums: List[int]) -> int:
        # 记忆化搜索
        n = len(nums)
        @cache
        def dfs(i: int, can_del: bool, inc: bool) -> int:
            if i == 0: return 1

            res =  1
            if nums[i-1] != nums[i] and (nums[i-1] < nums[i]) == inc:
                res = dfs(i-1, can_del, not inc) + 1
            if can_del and i > 1 and nums[i-2] != nums[i] and (nums[i-2] < nums[i]) == inc:
                res = max(res, dfs(i-2, False, not inc) + 1)
            return res

        ans = 0
        for i in range(n):
            ans = max(ans, dfs(i, True, True), dfs(i, True, False))
        dfs.cache_clear()
        return ans        