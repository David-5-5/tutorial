from math import inf
from typing import List

# 贪心专题 从最左/最右开始贪心
class Solution:
    def movesToMakeZigzag(self, nums: List[int]) -> int:
        # 自行解答
        n = len(nums)
        res1 = res2 = 0

        for i in range(1, n, 2):
            res1 += nums[i] - min(nums[i], min(nums[i-1], nums[i+1] if i+1<n else inf)-1)
        
        for i in range(0, n, 2):
            res2 += nums[i] - min(nums[i], min(nums[i-1] if i>0 else inf, nums[i+1] if i+1<n else inf)-1)
        
        return min(res1, res2)

if __name__ == "__main__":
    sol = Solution()
    nums = [9,6,1,6,2]
    print(sol.movesToMakeZigzag(nums))