from typing import List
from itertools import accumulate
from functools import lru_cache
class Solution:
    def stoneGameV(self, stoneValue: List[int]) -> int:
        '''
        Use dp array for memory search
        '''
        n = len(stoneValue)
        presum = list(accumulate(stoneValue, initial=0))  # prefix sum

        dp = [[-1 if i!=j else 0 for i in range(n)] for j in range(n)]

        
        def cal(l:int, r:int)-> int:

            if dp[l][r] != -1:return dp[l][r]
            if l + 1 == r:
                dp[l][r] = min(stoneValue[l],stoneValue[r])
                return dp[l][r]

            cur = 0
            lmax, rmin = l, r
            for i in range(l,r):
                if (presum[i+1]-presum[l]) * 2 < presum[r+1] - presum[l]:
                    lmax = i
                if (presum[i+1]-presum[l]) * 2 > presum[r+1] - presum[l]:
                    rmin = i
                    break
            
            rmin = min(rmin+1, r)
            for k in range(lmax,rmin): 
            # for k in range(l,r):
                if presum[k+1]-presum[l] > presum[r+1] - presum[k+1]:
                    cur = max(cur, cal(k+1,r) + presum[r+1] - presum[k+1])
                elif presum[k+1]-presum[l] < presum[r+1] - presum[k+1]:
                    cur = max(cur, cal(l,k) + presum[k+1]-presum[l])
                else: # equals
                    cur = max(cur, cal(l,k) + presum[k+1]-presum[l])
                    cur = max(cur, cal(k+1,r) + presum[r+1] - presum[k+1])
            
            dp[l][r] = cur
            return dp[l][r]

        cal(0,n-1)
        return dp[0][n-1]


    def stoneGameV_2(self, stoneValue: List[int]) -> int:
        '''
        Use lru_cache for memory search
        '''
        n = len(stoneValue)
        presum = list(accumulate(stoneValue, initial=0))  # prefix sum

        
        @lru_cache(maxsize = None)
        def cal(l:int, r:int)-> int:
            if l + 1 == r:
                return min(stoneValue[l],stoneValue[r])

            cur = 0
            for k in range(l,r):
                if presum[k+1]-presum[l] > presum[r+1] - presum[k+1]:
                    cur = max(cur, cal(k+1,r) + presum[r+1] - presum[k+1])
                elif presum[k+1]-presum[l] < presum[r+1] - presum[k+1]:
                    cur = max(cur, cal(l,k) + presum[k+1]-presum[l])
                else: # equals
                    cur = max(cur, cal(l,k) + presum[k+1]-presum[l])
                    cur = max(cur, cal(k+1,r) + presum[r+1] - presum[k+1])

            return cur
        
        return cal(0,n-1)


if __name__ == "__main__":
    sol = Solution()
    stoneValue = [98,77,24,49,6,12,2,44,51,96]
    stoneValue[::-1]
    # stoneValue = [4,9000,6,2,5,5,6,8,3,7,3,4,5,2,1,5,1,6,10,10,3,3,9,3,8,5,5,1,6,6,1,3,7,3,7,8,1,9,5,2,3,9,2,1,4,10,2,10,4,5,6,1,8,5,10,10,9,1,2,5,1,1,10,2,6,8,3,5,8,3,9,3,4,8,1,6,8,5,3,7,3,5,1,10,10,4,6,6,8,5,7,4,1,5,10,2,6,7,5,7,8,4,9,5,2,9,3,7,9,10,1,1,4,3,5,8,9,2,6,3,9,8,9,4,4,9,10,3,7,5,3,4,2,9,7,2,3,1,1,4,10,5,1,2,3,2,7,7,1,5,6,2,4,9,6,10,9,7,8,9,3,3,7,7,3,2,10,9,3,4,6,10,10,2,8,6,10,10,6,1,10,5,1,9,3,4,3,7,5,6,9,2,6,2,4,9,1,9,1,4,3,10,3,6,10,6,10,6,3,7,7,2,5,6,9,10,7,6,7,3,3,5,2,9,5,4,10,6,1,9,3,6,3,10,2,6,3,4,1,10,1,4,9,5,10,2,2,4,8,3,3,8,10,2,6,3,8,9,6,6,7,3,7,3,2,1,3,4,3,9,10,7,4,6,7,8,3,3,5,9,8,2,10,4,6,7,2,10,10,2,5,1,7,2,9,9,5,1,10,5,1,1,1,7,8,10,3,1,6,3,7,9,1,10,5,5,2,5,10,8,10,6,6,8,3,6,4,3,6,7,8,1,3,2,1,4,7,7,8,1,1,4,3,3,7,7,7,6,8,8,1,10,6,4,4,9,9,9,2,3,9,2,10,2,2,6,9,9,1,7,8,1,2,7,8,8,10,10,4,10,8,4,1,6,4,3,8,6,1,7,3,2,7,4,3,6,4,3,10,6,10,10,7,5,10,1,6,8,6,6,3,7,8,7,5,6,5,3,1,4,4,8,8,10,7,4,10,10,8,5,9,6,2,7,10,5,7,1,3,5,3,5,7,5,2,10,3,10,4,6,5,6,2,2,4,1,7,1,1,9,7,8,7,5,4,7,4,8,8,1,2,10,6,6,1,6,6,5,8,5,3,5,9,10,6,9,4,10,10,5,4,1,6000,12500,25000,50000,100000,200000,400000,990000]
    print(sol.stoneGameV_2(stoneValue))