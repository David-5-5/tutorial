from functools import cache
from math import inf
from typing import List


class Solution:
    def minCost(self, nums: List[int], k: int) -> int:
        n = len(nums)
        cost = [[0] * n for  _ in range(n)]
        
        for i in range(n-1,-1,-1):
            cnt,unique = [0] * n,  0
            for j in range(i, -1, -1):
                cnt[nums[j]] += 1
                if cnt[nums[j]] == 1:
                    unique += 1
                if cnt[nums[j]] == 2:
                    unique -= 1
                cost[j][i] = i - j + 1 - unique
        
        @cache
        def dfs(i:int) -> int:
            if i == n: return 0

            res = inf
            for j in range(i, n):
                res = min(res,  k  + cost[i][j] + dfs(j+1))
            return res
        return dfs(0)

if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,1,2,1,3,3], 2
    print(sol.minCost(nums, k))
                
        

        
