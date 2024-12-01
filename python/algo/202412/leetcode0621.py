from collections import Counter
from typing import List

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def leastInterval(self, tasks: List[str], n: int) -> int:
        cnt = Counter(tasks)

        m = len(tasks)

        if m < max(cnt.values()) * (n+1):
            m = max(cnt.values()) * (n+1)

        ans = i = begin = 0

        for _, cnt in sorted(cnt.items(), key=lambda p:-p[1]):
            for _ in range(cnt):
                ans = max(ans, i)
                i += (n+1)
                if i > m:
                    begin += 1
                    i = begin
        return ans