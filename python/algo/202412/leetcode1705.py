import heapq
from typing import List

# 贪心专题 - 其他区间
class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        # 自行解答
        h, n, i, ans = [], len(apples), 0, 0

        while h or i < n:
            if i < n:
                c, d = apples[i], days[i]
                if c:heapq.heappush(h, (d+i-1, c))
            
            while h and h[0][0] < i: # 过期的苹果
                heapq.heappop(h)
            
            if h:
                d, c = heapq.heappop(h)
                if c > 1: heapq.heappush(h, (d, c-1))
                ans += 1 # 吃到苹果
            i += 1
        return ans

        


