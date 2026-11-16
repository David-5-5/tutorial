from functools import cache
from typing import List


class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        # 自行解答， DP (刚开始按组合数学做，未找到正确解法)
        mod, n = 10 ** 9 + 7, len(nums)
       
        @cache
        def dfs(i: int, parity: int, cnt: int) -> int:
            if i < 0: return 1 if parity != 2 else 0

            res = dfs(i-1, parity, cnt) # 不选

            if parity == 2 or nums[i] % 2 != parity:
                res += dfs(i-1, nums[i] % 2, 1)
            else:
                if cnt < 2:
                    res += dfs(i-1, parity, cnt+1)
            res = res % mod
            return res
        
        ans = dfs(n-1, 2, 0)
        dfs.cache_clear()
        return ans


