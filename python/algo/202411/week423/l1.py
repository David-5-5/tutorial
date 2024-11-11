from typing import List


class Solution:
    def hasIncreasingSubarrays(self, nums: List[int], k: int) -> bool:
        n = len(nums)
        
        def check(l:int):
            for i in range(l+1, l+k):
                if nums[i-1] >= nums[i]:return False
            return True

        for i in range(n-2*k+1):
            if check(i) and check(i+k): return True
        return False

    
if __name__ == "__main__":
    sol = Solution()
    print(sol.hasIncreasingSubarrays([-15,3,16,0],2))