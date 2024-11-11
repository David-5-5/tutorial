from typing import List

# 双周赛 133
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        count = 0
        for i in range(n-2, -1, -1):
            if nums[i] != nums[i+1]:
                count += 1
        if nums[0] == 0 : count += 1
        return count
            
    
if __name__ == "__main__":
    sol = Solution()
    nums = [0,1,1,0,1]
    print(sol.minOperations(nums))