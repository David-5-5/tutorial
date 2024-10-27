from functools import cache
from math import gcd
from typing import List


class Solution:
    def subsequencePairCount(self, nums: List[int]) -> int:
        n = len(nums)
        MOD = 10 ** 9 + 7
        @cache
        def dfs(i:int, g1:int, g2:int) -> int:
            if i == n:
                if g1 == g2 and g1!=-1:
                    return 1
                else : return 0

            res = dfs(i+1, g1, g2) # 不选
            
            res += dfs(i+1, nums[i] if g1==-1 else gcd(nums[i], g1), g2)
            res += dfs(i+1, g1, nums[i] if g2==-1 else gcd(nums[i], g2))
            return res
        return dfs(0, -1, -1) % MOD
