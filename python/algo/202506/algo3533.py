from functools import cache
from typing import List

# 动态规划 - 输出具体方案
class Solution:
    def concatenatedDivisibility(self, nums: List[int], k: int) -> List[int]:
        n = len(nums)
        nums.sort()
        ans = []
        @cache
        def dfs(path: int, rem: int) -> bool:
            if path.bit_count() == n:
                return True if rem == 0 else False
                
            for i, v in enumerate(nums):
                if path >> i& 1: continue
                
                if dfs(path|1<<i, (rem*pow(10, len(str(v)))+v)%k):
                    ans.append(v)       # 归时输出具体方案
                    return True
            return False
        if not dfs(0, 0): return []
        ans.reverse()
        return ans

