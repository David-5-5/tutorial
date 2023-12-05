from typing import List
class Solution:
    '''同算法 面试题16.17 '''
    def maxSubArray(self, nums: List[int]) -> int:    
        res = nums[0]
        cul = nums[0]
        for i in range(1, len(nums)):
            if res < cul: res = cul
            if cul < 0:
                cul = nums[i]
            else:
                cul += nums[i]
        if res < cul: res = cul
        return res
