from collections import deque
from typing import List
class Solution:
    def findMaxValueOfEquation(self, points: List[List[int]], k: int) -> int:
        ans = - float("inf")
        q = deque()
        for x, y in points:
            while q and x - q[0][0] > k:
                q.popleft()
            while len(q) > 1 and q[0][1] - q[0][0] <= q[1][1] - q[1][0]: 
                q.popleft()
            while len(q) > 1 and q[-1][0]+q[-1][1]<=x+y and q[-1][1] - q[-1][0] <= y-x:
                q.pop()
            q.append((x, y))
            if len(q) > 1:
                ans = max(ans, q[-1][1] + q[-1][0] + q[0][1] - q[0][0])
        return ans

if __name__ == "__main__":
    sol = Solution()
    points, k = [[-19,-12],[-13,-18],[-12,18],[-11,-8],[-8,2],[-7,12],[-5,16],[-3,9],[1,-7],[5,-4],[6,-20],[10,4],[16,4],[19,-9],[20,19]], 6
    print(sol.findMaxValueOfEquation(points, k))      

        
