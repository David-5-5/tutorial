# 主站 84
from typing import List


class Solution:
    # 题目变更为 LCR 039
    # 简化
    def largestRectangleArea(self, heights: List[int]) -> int:
        heights.append(0) # 哨兵

        n  = len(heights)
        if n == 1: return heights[0]
        maxArea = 0
        stack = []
        for i in range(n):
            # 删除不必要的逻辑
            lens = 0
            while stack and stack[-1][0] > heights[i]:
                height, broad = stack.pop(-1)
                lens += broad
                maxArea = max(maxArea, height * lens)
            if heights[i] > 0:
                stack.append((heights[i], lens + 1))

        # lens = 0
        # while stack:
        #     height, broad = stack.pop(-1)
        #     lens += broad
        #     maxArea = max(maxArea, height * lens)

        return maxArea

    def largestRectangleArea2(self, heights: List[int]) -> int:
        heights.append(0) # 哨兵

        n  = len(heights)
        if n == 1: return heights[0]
        maxArea = 0
        stack = []
        for i in range(n):
            while stack and heights[stack[-1]] >= heights[i]:
                inx = stack.pop(-1)
                maxArea = max(maxArea, heights[inx] * (i-1-(stack[-1] if stack else -1)))
            stack.append(i)

        return maxArea

if __name__ == "__main__":
    sol = Solution()
    heights = [2,1,5,6,2,3]
    print(sol.largestRectangleArea(heights))
    print(sol.largestRectangleArea2(heights))