from functools import lru_cache
from typing import List


class Solution:
    def specialPerm(self, nums: List[int]) -> int:
        MOD = 10 ** 9 + 7
        n = len(nums)
        

        def is_spec(i: int, j:int) -> bool:
            if nums[i] % nums[j] == 0 or nums[j] % nums[i] == 0:
                return True
            return False

        @lru_cache(maxsize = None)
        def dfs(i:int, prev:int, sel:int):
            if i == n:
                return 1
            
            res = 0
            for next in range(n):
                if sel >> next & 1 == 0 and is_spec(prev, next):
                    res += dfs(i+1,next,sel | (1<<next))
            return res % MOD

        ans = 0
        for i in range(n):
            ans += dfs(1, i, 1 << i)
        return ans % MOD

if __name__ == "__main__":
    sol = Solution()
    nums  = [1,4,3]
    print(sol.specialPerm(nums))


