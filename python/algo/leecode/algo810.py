class Solution:
    def xorGame(self, nums) -> bool:
        n = len(nums)

        if n % 2 == 0: return True

        result=nums[0]

        for i in range(1, n):
            result ^= nums[i]
        
        if result == 0: return True
        else: return False
