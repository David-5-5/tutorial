from typing import List
from functools import lru_cache

from itertools import accumulate
class Solution:
    def stoneGameII(self, piles: List[int]) -> int:
        n = len(piles)

        presum = list(accumulate(piles, initial=0))

        @lru_cache(maxsize = None)
        def dp(begin: int, x: int, m: int):
            if begin + x >= n:
                return presum[n]-presum[begin]
            
            opp = 0

            for i in range(2*m):
                if begin+x+i+1 > n:
                    break;
                opp = max(opp, dp(begin+x, i+1, max(m, (i+1))))

            return presum[n]- presum[begin] - opp

        print(dp(0,2,2))
        return dp(0,1,1)



if __name__ == "__main__":
    sol = Solution()
    piles = [1,2,3,4,5,100]
    print(sol.stoneGameII(piles))