from math import inf
from typing import Counter

# 贪心专题
class Solution:
    def minDeletions(self, s: str) -> int:
        # 自行解答，感觉很简单，写起来容易错
        cnt = Counter(s)
        
        freq = sorted(cnt.values(), reverse=True)
        ans, prev =0, freq[0]
        
        for f in freq[1:]:
            if f >= prev:
                ans += f - prev + 1 if prev else f
                if prev: prev -= 1
            else:
                prev = f
        return ans


