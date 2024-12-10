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
    
    def maxSubArray2(self, nums: List[int]) -> int:
        # 前缀和及前缀和最小值
        res = nums[0]
        pre_mn = pre = 0
        
        for v in nums:
            pre += v
            if pre - pre_mn > res:
                res = pre - pre_mn
            if pre < pre_mn: pre_mn = pre

        return res
