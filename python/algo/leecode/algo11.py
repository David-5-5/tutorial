class Solution:
    def maxArea(self, height) -> int:
        n = len(height)
        if n < 2:
            return 0
        maxA = 0
        i = 0
        j = n-1
        while (i<j):
            maxA = max(maxA, min(height[i], height[j])*(j-i))
            if (height[i]>height[j]):
                j -= 1
            else:
                i += 1
        return maxA

if __name__ == "__main__":
    sol = Solution()
    height = [1,8,6,2,5,4,8,3,7]
    print(sol.maxArea(height))
