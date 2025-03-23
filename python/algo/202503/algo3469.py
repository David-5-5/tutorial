from functools import cache
from typing import List

# # 动态规划 - 多维 DP
class Solution:
    def minCost(self, nums: List[int]) -> int:
        # 自行解答 
        n = len(nums)
        if n < 3: return max(nums)

        @cache
        def dfs(i: int, prev:int) -> int:
            if i == n: return prev
            if i+1 == n: return max(prev, nums[i])

            sub = [prev, nums[i], nums[i+1]]
            sub.sort()
            return min(sub[2] + dfs(i+2, sub[0]), sub[1] + dfs(i+2, sub[2]))
        
        return dfs(1, nums[0])

    def minCost2(self, nums: List[int]) -> int:
        # 参考题解, 使用下标代替值域，便于改为递推
        n = len(nums)
        if n < 3: return max(nums)

        @cache
        def dfs(i: int, j:int) -> int:
            if i == n: return nums[j]
            if i+1 == n: return max(nums[j], nums[i])

            sub = [(nums[j],j), (nums[i],i), (nums[i+1],i+1)]
            sub.sort()
            return min(sub[2][0] + dfs(i+2, sub[0][1]), sub[1][0] + dfs(i+2, sub[2][1]))
        
        return dfs(1, 0)

if __name__ == "__main__":
    sol = Solution()
    print(sol.minCost([6,2,8,4]))