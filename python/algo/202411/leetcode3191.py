from typing import List

# 双周赛 133
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        for i in range(n-2):
            if nums[i] == 1:continue
            nums[i] = 1
            nums[i+1] = nums[i+1] ^ 1
            nums[i+2] = nums[i+2] ^ 1
            count += 1
        
        return count if nums[-1] == 1 and nums[-2] == 1 else -1
    
if __name__ == "__main__":
    sol = Solution()
    nums = [0,1,1,1,0,0]
    print(sol.minOperations(nums))