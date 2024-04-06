from typing import List
from functools import lru_cache

class Solution:
    # The count of piles is even, the subscript from 0, ... n-1
    # The plies could be divided into two groups: one group, subscript is even,
    # the other group, subscript is odd.
    # So Alice select 0/n-1, so the Bob select odd 1, n-1. or even 0, n-2
    # So Alice compare the two group, select the large group, She alway win.
    def stoneGame(self, piles: List[int]) -> bool:
        return True

# The dp solution refer to 486

if __name__ == "__main__":
    sol = Solution()
    piles = [5,3,4,5]
    print(sol.stoneGame(piles))