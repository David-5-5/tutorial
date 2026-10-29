from typing import List


class Solution:
    def taskSchedulerII(self, tasks: List[int], space: int) -> int:
        last = {}
        ans = 0
        for t in tasks:
            ans += 1
            if t in last and last[t] + space + 1 > ans:
                ans = last[t] + space + 1
            last[t] = ans
        return ans