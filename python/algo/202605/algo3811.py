from functools import cache
from typing import List

# 六、状态机 DP - 6.3 进阶
class Solution:
    def alternatingXOR(self, nums: List[int], target1: int, target2: int) -> int:
        # 自行解答
        mod = 10 ** 9 + 7
        n = len(nums)

        @cache
        def dfs(i: int, s_xor:int, exp: int) -> int:
            if i == n-1:
                if s_xor == exp: return 1
                else: return 0
            
            res = dfs(i+1, s_xor ^ nums[i+1], exp)
            if s_xor == exp:
                res += dfs(i+1, nums[i+1], (target2 if exp==target1 else target1))
            
            return res % mod
        ans = dfs(0, nums[0], target1)
        dfs.cache_clear()
        return ans
