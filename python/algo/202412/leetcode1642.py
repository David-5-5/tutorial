import heapq
from typing import List

# 贪心专题 - 反悔贪心
class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        # 自行解答
        n = len(heights)
        # 定义两个堆，分别存储使用的bricks次数，以及使用 l 等于 bricks 的数量
        # 其中使用 bricks 使用大顶堆，使用 ladders 小顶堆
        # 当 bricks 和 ladders 不够时，如果使用梯子的bricks的数量小于使用 bricks 的堆，则交换，则
        # 现有的 bricks 的数量会增加 
        useb , usel = [], []

        for i in range(1, n):
            if heights[i-1] >= heights[i]: continue

            while useb and usel and -useb[0] > usel[0]:
                b1 = - heapq.heappop(useb)
                b2 = heapq.heappop(usel)
                bricks += b1 - b2
                heapq.heappush(useb, -b2)
                heapq.heappush(usel, b1)

            if heights[i] - heights[i-1] <= bricks:
                heapq.heappush(useb, heights[i-1]-heights[i])
                bricks -= heights[i] - heights[i-1]
                # 愚蠢的错误，heights[i] - heights[i-1]并不是最大的值，不一定在栈顶
                # bricks += useb[0] # 
            elif ladders:
                ladders -= 1
                heapq.heappush(usel, heights[i] - heights[i-1])
            else:
                return i - 1
        
        return n-1

if __name__ == "__main__":
    sol = Solution()
    heights, bricks, ladders = [14,3,19,3], 17, 0
    print(sol.furthestBuilding(heights, bricks, ladders))