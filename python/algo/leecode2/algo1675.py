from typing import List
from bisect import bisect_right
import heapq
class Solution:
    def minimumDeviation(self, nums: List[int]) -> int:
        nums.sort()
        res = nums[-1] + 1
        inx = 0
        while nums[inx] % 2 == 1 and inx+1 < len(nums):
            res = min(res, max(nums[-1], 2*nums[inx]) - nums[inx+1])
            inx += 1 


        loop = []
        change = True
        while change and res>0:
            res = min(res, nums[-1] - nums[0])

            if nums[-1] % 2 == 0 and (nums[0] % 2 == 0 or max(nums[-2]-nums[0], nums[-2]-nums[-1]//2) < max(nums[-1]-nums[1], 2*nums[0]-nums[1])):
                div = nums.pop(-1) // 2
                inx = bisect_right(nums, div)
                nums.insert(inx, div)
                if inx == 0: loop.append(div)
            elif nums[0] % 2 == 1:
                mul = nums.pop(0) * 2
                inx = bisect_right(nums, mul)
                nums.insert(inx, mul)
                if inx+1 == len(nums): loop.append(mul)
            else:
                change = False

            if len(loop) == 3 and loop[0] == loop[2]:
                return res
            elif len(loop) == 3:
                loop.pop(0)

        return res
    
    def minimumDeviation2(self, nums: List[int]) -> int:
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
