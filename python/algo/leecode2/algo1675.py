from typing import List
from bisect import bisect_right
import heapq
class Solution:

    def minimumDeviation(self, nums: List[int]) -> int:
        # Base on algo 632
        newnums = []
        for num in nums:
            sub = [num]
            if num % 2 == 0:
                while num % 2 == 0:
                    num //= 2
                    sub.append(num)
            else:
                sub.append(num*2)
            sub.sort()
            newnums.append(sub)

        def smallestRange(nnums):
            rows = len(nnums)
            hq = []
            curUpper = -10 ** 5 
            for i in range(rows):
                curUpper = max(curUpper, nnums[i][0])
                heapq.heappush(hq, (nnums[i][0], (i,0)))
            curLower, pos = heapq.heappop(hq)
            upper = curUpper
            lower = curLower
            while True:
                if upper - lower == 0:break
                if pos[1] + 1 < len(nnums[pos[0]]):
                    curUpper = max(curUpper, nnums[pos[0]][pos[1]+1])
                    heapq.heappush(hq, (nnums[pos[0]][pos[1]+1], (pos[0],pos[1]+1)))
                else:
                    break
                
                curLower, pos = heapq.heappop(hq)
                if upper - lower > curUpper - curLower:
                    lower = curLower
                    upper = curUpper
            
            return [lower, upper]

        distinct = smallestRange(newnums)
        return distinct[1] - distinct[0]
if __name__ == "__main__":
    sol = Solution()
    nums = [1,2,3,4]
    print(sol.minimumDeviation2(nums))
