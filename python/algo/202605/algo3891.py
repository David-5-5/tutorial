from functools import cache
from typing import List

# 六、状态机 DP - 6.3 进阶
class Solution:
    def minIncrease(self, nums: List[int]) -> int:
        # 自行解答
        n = len(nums)
        if n % 2 == 1:
            ans = 0
            for i in range(1, n, 2):
                ans += max(max(nums[i-1], nums[i+1]) - nums[i] + 1, 0)
            return ans

        @cache
        def dfs(i:int, l:int) -> int:
            if i < 1: return 0
            res = max(max(nums[i-1], nums[i+1]) - nums[i] + 1, 0) + dfs(i-2, l) # 不选
            if l:
                res = min(res, dfs(i-1, 0))
            return res
        return dfs(n-2, 1)

    def minIncrease(self, nums: List[int]) -> int:
        # 代码优化 性能一般
        n = len(nums)

        @cache
        def dfs(i:int, l:int) -> int:
            if i < 1: return 0
            res = max(max(nums[i-1], nums[i+1]) - nums[i] + 1, 0) + dfs(i-2, l) # 不选
            if l:
                res = min(res, dfs(i-1, 0))
            return res
        return dfs(n-2, (n-1)%2)