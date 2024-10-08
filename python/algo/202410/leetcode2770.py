from functools import cache
from math import inf
from typing import List

# 周赛 353
class Solution:
    def maximumJumps(self, nums: List[int], target: int) -> int:
        # 自行解答，记忆化搜索
        n = len(nums)
        @cache
        def dfs(i:int) -> int:
            if i == n-1: return 0

            res = -inf
            for j in range(i+1, n):
                if abs(nums[i]-nums[j]) <= target:
                    res = max(res, 1+dfs(j))
            return res
        ans = dfs(0)
        return ans if ans != -inf else -1

if __name__ == "__main__":
    sol = Solution()
    nums, target = [1,3,6,4,1,2], 2
    print(sol.maximumJumps(nums, target))