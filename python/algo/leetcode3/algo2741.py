from functools import cache, lru_cache
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
    
    def specialPerm2(self, nums: List[int]) -> int:
        # 202506 复习
        MOD = 10 ** 9 + 7
        n = len(nums)
        
        @cache
        def dfs(i:int, p:int):
            if i == 0:
                return 1
            
            res = 0
            for cur in range(n):
                if i >> cur & 1 == 1 and (nums[p] % nums[cur] == 0 or nums[cur] % nums[p] == 0):
                    res += dfs(i ^ (1<<cur),cur)
            return res % MOD

        ans = 0
        for i in range(n):
            ans += dfs(((1<<n)-1)^(1<<i), i)
        return ans % MOD    
    
if __name__ == "__main__":
    sol = Solution()
    nums  = [1,4,3]
    print(sol.specialPerm(nums))


