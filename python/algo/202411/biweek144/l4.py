from functools import cache
from math import inf
from typing import List


class Solution:
    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        ans = 0
        n = len(fruits)
        ans = sum(fruits[i][i] for i in range(n))

        @cache
        def dfs_i(i:int, j:int)->int:
            if i == n-1:
                if j == n-1: return 0
                else : return -inf
            
            if i >= j: return -inf

            res = 0
            for n_j in [j-1,j,j+1]:
                if 0<=n_j<n:
                    res = max(res, dfs_i(i+1,n_j))
            
            return res + fruits[i][j]
            
        @cache
        def dfs_j(i:int, j:int)->int:
            if j == n-1:
                if i == n-1:return 0
                else : return -inf

            if i <= j: return -inf
            
            res = 0
            for n_i in [i-1,i,i+1]:
                if 0<=n_i<n:
                    res = max(res, dfs_j(n_i,j+1))
            
            return res + fruits[i][j]

        return ans + dfs_i(0,n-1) + dfs_j(n-1, 0)
    
if __name__ == "__main__":
    sol = Solution()
    print(sol.maxCollectedFruits([[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]))