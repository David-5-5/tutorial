from typing import List


class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        k = 0
        for i in range(1, len(nums)): # 从第二个元素开始遍历
            if nums[i] != nums[k]:
                k += 1
                nums[k] = nums[i]
                
        del nums[k+1:]
        return k+1
            