from typing import Counter


class Solution:
    def minFlips(self, s: str) -> int:
        cnt = Counter(s)

        if cnt['0'] == 0 or cnt['1'] <= 1: return 0
        return min(cnt['0'], cnt['1'] - 1 - (1 if s[0] == s[-1] == '1' else 0))
