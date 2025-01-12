from math import inf
from typing import List

# 3357
class Solution:
    def minDifference(self, nums: List[int]) -> int:
        # 参考题解，区间贪心
        minL, maxR, n = inf, 0, len(nums)
        for v in nums:
            if minL > v: minL = v
            if maxR < v: maxR = v
        
        ans = 0
        if minL >= maxR: return 0

        for i, v in enumerate(nums):
            if nums[i] == -1:
                l, r = minL, maxR
                if i > 0: l = nums[i-1]
                if i + 1 < n: r = nums[i+1]
                if l == -1 or r == -1:
                    ans = max(ans, (maxR - minL + 2)//3)
                else:
                    ans = max(ans, min(r-minL, maxR-l))
                    

        
    
if __name__ == "__main__":
    sol = Solution()
    print(sol)