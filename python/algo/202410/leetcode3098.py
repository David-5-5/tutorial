from functools import cache
from math import inf
from typing import List



# 双周赛 127
class Solution:
    def sumOfPowers(self, nums: List[int], k: int) -> int:
        
        # 参考题解
        # 记忆化搜索
        # dfs(i，l, prev , diff) 
        # i当前下标, l 已选子序列长度, 前一个选择的值，用于计算差，diff 子序列中最小差
        # 边界条件 l == 0 or l > i + 1
        # 选 dfs(i-1, l-1, nums[i], min(abs(prev-nums[i]), diff))
        # 不选 dfs(i-1, l, prev, diff)
        # 时间复杂度 n^5 : 50 ** 5
        MOD = 10 ** 9 + 7
        nums.sort()

        @cache
        def dfs(i:int, l:int, prev, diff):
            if l == 0: return diff
            if l > i + 1: return 0

            
            # 选 dfs
            res = dfs(i-1, l-1, nums[i], min(prev - nums[i], diff))

            # 不选
            res += dfs(i-1, l, prev, diff)

            return res % MOD

        return dfs(len(nums)-1, k, inf, inf)


if __name__ == "__main__":
    sol = Solution()
    nums, k = [4,3,-1], 2
    print(sol.sumOfPowers(nums, k))