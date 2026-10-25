import string
from typing import Counter

class Solution:
    def minSteps(self, s: str, t: str) -> int:
        cnt_s, cnt_t = Counter(s), Counter(t)

        ans = 0
        for c in string.ascii_lowercase:
            ans += abs(cnt_s[c] - cnt_t[c])
        return ans
