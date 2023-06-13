import heapq
class Solution:
    def smallestRange(self, nums):
        rows = len(nums)

        hq = []
        curUpper = -10 ** 5 
        for i in range(rows):
            curUpper = max(curUpper, nums[i][0])
            heapq.heappush(hq, (nums[i][0], (i,0)))
        curLower, pos = heapq.heappop(hq)
        upper = curUpper
        lower = curLower
        while True:
            if upper - lower == 0:break
            if pos[1] + 1 < len(nums[pos[0]]):
                curUpper = max(curUpper, nums[pos[0]][pos[1]+1])
                heapq.heappush(hq, (nums[pos[0]][pos[1]+1], (pos[0],pos[1]+1)))
            else:
                break
            
            curLower, pos = heapq.heappop(hq)
            if upper - lower > curUpper - curLower:
                lower = curLower
                upper = curUpper
        
        return [lower, upper]

if __name__ == "__main__":
    sol = Solution()

    #nums = [[1,2,3],[1,2,3],[1,2,3]]
    nums = [[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
    import random
    from datetime import datetime
    begin = datetime.now()
    print(sol.smallestRange(nums))
    print((datetime.now()- begin).total_seconds())

