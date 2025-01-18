from typing import List


class Solution:
    def maxAdjacentDistance(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n):
           ans = max(ans, abs(nums[i-1]-nums[i]) )
        return ans

        
if __name__ == "__main__":
    sol = Solution()
    print(sol)