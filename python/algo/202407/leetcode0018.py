from bisect import bisect_left, bisect_right
from collections import defaultdict
from typing import List

class Solution:
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:

        nums.sort()
        n = len(nums)
        ans = []

        for begin in range(n-3):
            # pruning 
            if nums[begin] + nums[begin+1] + nums[begin+2] + nums[begin+3] > target:break
            if 0<begin<n and nums[begin] == nums[begin-1]: continue # skip the equals

            for end in range(n-1, begin+1, -1):        

                if nums[end-3] + nums[end] + nums[end-1] + nums[end-2] < target: break
                if end<n-1 and nums[end] == nums[end+1]: continue

                l = begin + 1
                r = end -1
                while l < r:
                    s = nums[begin] + nums[l] + nums[r] + nums[end]
                    if s < target:
                        l += 1
                    elif s > target:
                        r -= 1
                    else:
                        ans.append([nums[begin], nums[l], nums[r], nums[end]])
                        l += 1
                        while l < r and nums[l] == nums[l-1]: # skip the equals
                            l += 1 
                        r -= 1
                        while r > l and nums[r] == nums[r+1]: # skip the equals
                            r -= 1

        return ans
    

if __name__ == "__main__":
    sol = Solution()
    nums, target = [1,0,-1,0,-2,2], 0
    
    print(sol.fourSum(nums, target))