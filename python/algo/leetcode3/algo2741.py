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

        # 倒序，便于改为递推
        tot = (1<<n)-1
        return sum(dfs(tot^(1<<i), i) for i in range(n))% MOD
    

    def specialPerm3(self, nums: List[int]) -> int:
        # 202506 复习 递归-递推
        MOD = 10 ** 9 + 7
        n = len(nums)
        tot = (1<<n)-1
        
        dp = [[0] * n for _ in range(tot)]
        for i in range(n): dp[0][i] = 1

        for s in range(1, tot):                 # 状压情况下，递推效率不高
            for i, prev in enumerate(nums):
                if s >> i & 1: continue
                for j, x in enumerate(nums):
                    if s>>j & 1 and (prev % x==0 or x% prev ==0):
                        dp[s][i] += dp[s^(1<<j)][j]

        return sum(dp[tot^(1<<i)][i] for i in range(n))% MOD
 
if __name__ == "__main__":
    sol = Solution()
    nums  = [1,4,3]
    print(sol.specialPerm(nums))


