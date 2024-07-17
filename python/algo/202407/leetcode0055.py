from typing import List

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        max_r = 0
        for i, num in enumerate(nums):
            if i <= max_r:
                max_r = max(max_r, i + num)
                if max_r >= len(nums) - 1: return True
            else: return False

if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,1,0,4]
    nums = [2,3,1,1,4]
    print(sol.canJump(nums))