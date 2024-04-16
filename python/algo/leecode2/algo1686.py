from typing import List
from collections import deque
class Solution:
    def stoneGameVI(self, aliceValues: List[int], bobValues: List[int]) -> int:
        n = len(aliceValues)
        diff = [aliceValues[i]-bobValues[i] for i in range(n)]

        aValue = 0
        bValue = 0
        dq = deque(sorted(enumerate(diff), key=lambda p:p[1]))
        isAlice = True
        while dq:
            if abs(dq[0][1]) > abs(dq[-1][1]):
                inx, _ = dq.popleft()
            else:
                inx, _= dq.pop()
            
            if isAlice:
                aValue += aliceValues[inx]
                isAlice = False
            else:
                bValue += bobValues[inx]
                isAlice = True
        
        if aValue == bValue:
            return 0
        elif aValue > bValue:
            return 1
        else: return -1

if __name__ == "__main__":
    sol = Solution()
    aliceValues, bobValues = [1,2], [3,1]
    aliceValues, bobValues = [9,8,3,8], [10,6,9,5]
    print(sol.stoneGameVI(aliceValues, bobValues))