import heapq
class Solution:
    # 每个列表都是非递减排列 的整数列表，因此可以从k个整数列表的第一个元素开始遍历，
    # 并记录当前选择的k个列表中的值区间，并找出最小的区间：
    # 初始化区间：
    # nums[0][0]
    # nums[1][0]
    # ……
    # nums[k][0]
    # 
    # 初始的区间即为 [min(nums[0][0], nums[1][0],……,nums[k][0]), 
    #               max(nums[0][0], nums[1][0],……,nums[k][0])]
    # 
    # 接下来由于列表都是非递减排列的整数列表，因此选择nums[0][0], nums[1][0],……,
    # nums[k][0]最小值所在的列表i，并选择下一个元素，组成新的区间nums[0][0], 
    # nums[1][0],…nums[i][1],…,nums[k][0]，重新计算最小值及最大值。
    # 由于是非递减排列的整数列表，选择最小数的列表的下一个元素，有助于增大最小值，并减少max-min的值。
    # 结束条件：
    # - 当找到max-min=0时，终止
    # - 当前k个整数列表区间的最小值，在其列表中为最后一个值。因为遍历非最小值的列表后续记录，
    #   不会更改最小值，但会增加最大值，导致区间增大。

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

