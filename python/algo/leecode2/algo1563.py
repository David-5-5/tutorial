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
            if l == r: return 0
            if l + 1 == r:
                dp[l][r] = min(stoneValue[l],stoneValue[r])
                return dp[l][r]

            cur = 0
            # lmax, rmin = l, r
            # for i in range(l,r):
            #     if (presum[i+1]-presum[l]) * 2 < presum[r+1] - presum[l]:
            #         lmax = i
            #     if (presum[i+1]-presum[l]) * 2 > presum[r+1] - presum[l]:
            #         rmin = i
            #         break
            
            # rmin = min(rmin+1, r)
            # for k in range(lmax,rmin): 
            for k in range(l,r):
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
            if l == r: return 0
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
    print(sol.stoneGameV_2(stoneValue))