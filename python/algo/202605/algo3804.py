from typing import List


class Solution:
    def centeredSubarrays(self, nums: List[int]) -> int:
        ans = 0
        n = len(nums)
        
        for i in range(n):
            num_set = set()
            pre_sum = 0
            
            for j in range(i, n):
                pre_sum += nums[j]
                num_set.add(nums[j])
                
                # 如果集合里包含当前前缀和，答案 +1
                if pre_sum in num_set:
                    ans += 1
                    
        return ans        