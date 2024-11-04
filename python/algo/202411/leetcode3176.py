from functools import cache
from typing import List

# 双周赛 132
class Solution:
    def maximumLength(self, nums: List[int], k: int) -> int:
        # 参考最长子序列的朴素DP，用枚举选那个。
        # 选或不选需要 dfs 需要两个参数，相比较与枚举选哪个 时间复杂度相同，空间复杂度大
        @cache
        def dfs(i:int, j:int) -> int:
            if i == 0: return 1

            res = 1
            for x in range(i):
                if nums[x] == nums[i]: res = max(res, 1 + dfs(x, j))
                else:
                    if j: res = max(res, 1 + dfs(x, j-1))
            return res

        return max(dfs(i, k) for i in range(len(nums)))

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3,4,5,1], 0
    nums, k = [1,2,1,1,3], 2
    nums, k = [15,6,26,32,6], 1
    print(sol.maximumLength(nums, k))