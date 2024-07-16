from bisect import bisect_left, bisect_right
from collections import defaultdict
from typing import List

# refer to https://www.bilibili.com/video/BV1bP411c7oJ/
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:

        nums.sort()
        n = len(nums)
        ans = []

        for i in range(n-2):
            if 0<i<n and nums[i] == nums[i-1]: # skip the equals
                continue
            
            # two pruning 
            if nums[i] + nums[i+1] + nums[i+2] > 0:break
            
            if nums[i] + nums[-1] + nums[-2] < 0: continue

            j = i + 1
            k = n -1
            while j < k:
                s = nums[i] + nums[j] + nums[k]
                if s < 0:
                    j += 1
                elif s > 0:
                    k -= 1
                else:
                    ans.append([nums[i], nums[j], nums[k]])
                    j += 1
                    while j < k and nums[j] == nums[j-1]: # skip the equals
                        j += 1 
                    k -= 1
                    while k > j and nums[k] == nums[k+1]: # skip the equals
                        k -= 1

        return ans
    

if __name__ == "__main__":
    sol = Solution()
    nums = [0,0,0]
    
    print(sol.threeSum(nums))