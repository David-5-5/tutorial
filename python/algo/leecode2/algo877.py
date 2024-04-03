from typing import List
from functools import lru_cache

class Solution:
    def stoneGame(self, piles: List[int]) -> bool:
        # return True

        @lru_cache(maxsize = None)
        def stone(l:int, r:int):
            if (l == r): return piles[l]

            return max(piles[l]+stone(l+1,r), piles[r]+stone(l,r-1))

        return stone(0, len(piles)-1)

if __name__ == "__main__":
    sol = Solution()
    piles = [5,3,4,5]
    print(sol.stoneGame(piles))