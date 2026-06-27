from itertools import permutations
from typing import List

class Solution:
    def permutation(self, S: str) -> List[str]:
        return ["".join(sub) for sub in permutations(S)]