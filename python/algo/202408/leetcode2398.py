from collections import deque
from typing import List

# 双周赛 86
class Solution:
    def maximumRobots(self, chargeTimes: List[int], runningCosts: List[int], budget: int) -> int:

        ans = s = l = 0
        q = deque()
        for r, (charge, cost) in enumerate(zip(chargeTimes, runningCosts)):
            # 及时清除队列中的无用数据，保证队列的单调性
            while q and chargeTimes[q[-1]] <= charge:
                q.pop()
            q.append(r)
            s += cost
            
            while q and (r - l + 1) * s + chargeTimes[q[0]] > budget:
                s -= runningCosts[l]
                l += 1
                if l > q[0]:  # 及时清除队列中的无用数据，保证队列的单调性
                    q.popleft()

            ans = max(ans, r - l + 1)
        return ans

if __name__ == '__main__':
    print(Solution().maximumRobots([3,6,1,3,4], [2,1,3,4,5], 25))