class Solution:
    def largestRectangleArea(self, heights) -> int:
        n  = len(heights)
        if n == 1: return heights[0]
        maxArea = 0
        stack = []
        for i in range(n):
            if len(stack) == 0 or stack[-1][0] <= heights[i]:
                if heights[i] > 0:
                    stack.append((heights[i], 1))
            else:
                lens = 0
                while stack and stack[-1][0] > heights[i]:
                    height, broad = stack.pop(-1)
                    lens += broad
                    maxArea = max(maxArea, height * lens)
                if heights[i] > 0:
                    stack.append((heights[i], lens + 1))

        lens = 0
        while stack:
            height, broad = stack.pop(-1)
            lens += broad
            maxArea = max(maxArea, height * lens)

        return maxArea

if __name__ == "__main__":
    sol = Solution()
    heights = [2,1,5,6,2,3]
    print(sol.largestRectangleArea(heights))