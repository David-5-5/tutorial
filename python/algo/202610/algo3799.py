from itertools import permutations
from typing import List


class Solution:
    def wordSquares(self, words: List[str]) -> List[List[str]]:
        ans = []
        for t, l, r, b in permutations(words, 4):
            if t[0] == l[0] and t[3] == r[0] and b[0] == l[3] and b[3] == r[3]:
                ans.append([t, l, r, b])
        ans.sort()
        return ans