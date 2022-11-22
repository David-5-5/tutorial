class Solution:
    def trap(self, height) -> int:
        if len(height) <= 2: return 0

        n = len(height)
        maxHeight = max(height)
        water = [maxHeight for _ in range(n)]
        queue = []
        for i in (0, n-1):
            if water[i] > height[i]:
                water[i] = height[i]
                queue.append(i)
        adj = [-1, 1]
        while queue:
            pos = queue.pop(0)
            for k in adj:
                if pos + k < 0 or pos + k >= n:
                    continue 
                
                if water[pos + k] > water[pos] and water[pos + k] > height[pos + k]:
                    water[pos + k] = max(water[pos], height[pos + k])
                    queue.append(pos + k)
        res = 0
        for i in range(n):
            res += water[i] - height[i]
        return res

    def trap2(self, height) -> int:
        if len(height) <= 2: return 0
        n = len(height)

        leftMax = [height[0]  for _ in range(n)]
        rightMax = [height[n-1] for _ in range(n)]
        for i in range(1, n):
            leftMax[i] = max(leftMax[i-1], height[i])

        for i in range(n-2, -1, -1):
            rightMax[i] = max(rightMax[i+1], height[i])
        
        res = 0
        for i in range(1, n-1):
            res += min(leftMax[i],rightMax[i]) - height[i]
        return res

    def trap3(self, height) -> int:
        if len(height) <= 2: return 0
        n = len(height)
        stack = []
        stack.append(0)
        res = 0
        for i in range(1, n):
            while len(stack)>0 and height[i] > height[stack[-1]]:
                top = stack.pop()
                if len(stack) > 0:
                    res += (min(height[stack[-1]], height[i]) - height[top]) * (i - stack[-1] - 1)
            stack.append(i)        
        return res

    def trap4(self, height) -> int:
        if len(height) <= 2: return 0
        n = len(height)
        left, right, leftMax, rightMax = 0, n-1, 0, 0

        res = 0
        while left < right:
            if height[left] < height[right]:
                leftMax = max(leftMax, height[left])
                res += leftMax - height[left]
                left += 1
            else:
                rightMax = max(rightMax, height[right])
                res += rightMax - height[right]
                right -= 1 

        return res

if __name__ == "__main__":
    sol = Solution()
    # input = [0,1,0,2,1,0,1,3,2,1,2,1]
    input = [4,2,0,3,2,5]
    print(sol.trap(input))
    print(sol.trap2(input))
    print(sol.trap3(input))
    print(sol.trap4(input))