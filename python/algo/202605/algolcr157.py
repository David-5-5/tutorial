from itertools import permutations
from typing import List

# LCR series
class Solution:
    def goodsOrder(self, goods: str) -> List[str]:
        return list(set([''.join(p) for p in permutations(goods)]))  