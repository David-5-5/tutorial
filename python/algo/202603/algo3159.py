from typing import List

# 顺序
class Solution:
    def occurrencesOfElement(self, nums: List[int], queries: List[int], x: int) -> List[int]:
        # 自行解答，模拟
        x_nums = []
        for i, v in enumerate(nums):
            if v == x: x_nums.append(i)
        
        ans = []

        for q in queries:
            if q > len(x_nums): ans.append(-1)
            else: ans.append(x_nums[q-1])
        return ans