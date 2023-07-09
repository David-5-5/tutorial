from functools import lru_cache
import collections
import math
class Solution:
    def numSquarefulPerms(self, nums) -> int:
        n = len(nums)

        def isSquare(val : int) -> bool:
            if val == int(val ** .5) ** 2:
                return True
            else:
                return False
        
        @lru_cache(maxsize=None)
        def dfs(i, visited):
            if visited == (1 << n) - 1:
                return 1
            
            count = 0
            for j in range(n):
                if i != j and isSquare(nums[i]+nums[j]) and visited & 1 << j == 0:
                    count += dfs(j, visited | 1 << j)
            return count

        count = 0 
        for i in range(n):
            count += dfs(i, 1 << i)
        
        distinct = collections.Counter(nums)
        for v in distinct.values():
            count //= math.factorial(v)

        return count
    
if __name__ == "__main__":
    sol = Solution()
    s = [1,17,8]
    print(sol.numSquarefulPerms(s))