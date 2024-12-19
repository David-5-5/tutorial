import heapq
from typing import List

# 贪心专题 - 其他区间
class Solution:
    def maxEvents(self, events: List[List[int]]) -> int:
        h = []

        events.sort()
        ans, t = 0, 1
        while h or events:
            while events and events[0][0] <= t:
                _, end = events.pop(0)
                heapq.heappush(h, end)
            
            while h and h[0] < t:
                heapq.heappop(h)
            
            if h:
                heapq.heappop(h)
                ans += 1
            t += 1
        return ans