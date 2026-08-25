from cmath import inf
from functools import cache
from typing import List


class Solution:
    def minimizeConcatenatedLength(self, words: List[str]) -> int:
        n = len(words)

        @cache
        def dfs(i: int, head: str, tail: str) -> int:
            if i == n: return 0

            res = inf
            res = min(res, len(words[i]) + dfs(i+1, head, words[i][-1]) - (1 if tail == words[i][0] else 0))
            res = min(res, len(words[i]) + dfs(i+1, words[i][0], tail) - (1 if head == words[i][-1] else 0))
            return res
        return len(words[0]) + dfs(1, words[0][0], words[0][-1])
