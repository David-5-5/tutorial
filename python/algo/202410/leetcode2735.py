from typing import List

# 周赛 349
class Solution:
    def minCost(self, nums: List[int], x: int) -> int:
        # 自行解答
        ans, n = 0, len(nums)
        
        for i in range(n):
            mx = nums[i]
            for step in range(1, n):
                
                mx = min(mx, nums[(i+step)%n]+step*x)
            ans += mx
        
        return ans