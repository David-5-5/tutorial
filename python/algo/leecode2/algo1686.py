from typing import List
from collections import deque
class Solution:
    def stoneGameVI(self, aliceValues: List[int], bobValues: List[int]) -> int:
        n = len(aliceValues)
        addv = [aliceValues[i]+bobValues[i] for i in range(n)]

        asum = 0
        bsum = 0
        aorb = 0
        for i, _ in sorted(enumerate(addv), key=lambda p:p[1], reverse=True):
            if aorb == 0:
                asum += aliceValues[i]
            else:
                bsum += bobValues[i]

            aorb ^= 1

        if asum > bsum:
            return 1
        elif asum == bsum:
            return 0
        else:
            return -1


if __name__ == "__main__":
    sol = Solution()
    aliceValues, bobValues = [1,2], [3,1]
    aliceValues, bobValues = [2,4,3], [1,6,7]
    print(sol.stoneGameVI(aliceValues, bobValues))