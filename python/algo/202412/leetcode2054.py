from collections import deque
from math import inf
from typing import List

# 贪心专题 - 其他区间
class Solution:
    def maxTwoEvents(self, events: List[List[int]]) -> int:
        # 按照结束时间排列并计算前缀最大values
        events.sort(key=lambda p:p[1])
        ans = -inf
        qu = deque()

        for _, r, v in events:
            if qu and qu[-1][0] == r:
                qu[-1][1] = max(qu[-1][1], v)
                continue
            if qu and qu[-1][1] >= v:continue
            qu.append([r, v])
        
        events.sort(key=lambda p:p[0])

        for l, _, v in events:
            while len(qu) > 1 and qu[1][0] < l:
                qu.popleft()
            if qu and qu[0][0] < l:
                ans = max(ans, qu[0][1]+v)
            else:
                ans = max(ans, v)
        return ans