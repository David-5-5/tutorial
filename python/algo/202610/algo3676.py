from typing import List

class Solution:
    def bowlSubarrays(self, nums: List[int]) -> int:
        ans, st = 0, []

        for i, x in enumerate(nums):
            while st and nums[st[-1]] < x:
                if i - st.pop() > 1: ans += 1
            
            if st and nums[st[-1]] > x:
                if i - st[-1] > 1: ans += 1
            st.append(i)
        
        return ans