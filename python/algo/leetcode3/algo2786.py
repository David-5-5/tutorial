from functools import lru_cache
from typing import List
class Solution:
    # 最好理解的 DP 默认选 0, 从 1 开始状态转移
    # dp[i,j] i 表示当前元素，已经选择了前i-1个元素
    #         j 表示上一个已选择元素的奇偶
    def maxScore(self, nums: List[int], x: int) -> int:
        n = len(nums)

        @lru_cache(maxsize=None)
        def f(i:int, j:int):
            if i == n:
                return 0
            
            # select
            res = f(i+1, nums[i]%2) + nums[i] - (x if j!=nums[i]%2 else 0)
            return max(f(i+1, j), res)
        
        return f(1, nums[0]%2) + nums[0]

    # 从 0 开始状态转移，便于后续的改为递推
    def maxScore2(self, nums: List[int], x: int) -> int:
        n = len(nums)

        @lru_cache(maxsize=None)
        def f(i:int, j:int):
            if i == n:
                return 0
            if nums[i]%2 != j:
                return f(i+1, j)
            return max(f(i+1, nums[i]%2), f(i+1,nums[i]%2^1)-x)+nums[i]
        
        return f(0, nums[0]%2)
    
    # 从 0 开始状态转移，便于后续的改为递推
    def maxScore3(self, nums: List[int], x: int) -> int:
        dp = [0, 0]
        for v in reversed(nums):
            dp[v%2] = max(dp[v%2],dp[v%2^1]-x) + v
        return dp[nums[0]%2]
        # return max(dp) 


    # 后续如果把题目改为第一个可选可不选，递推的写法最后改为 return max(dp)即可
    # 递归的写法
    # 从 0 开始状态转移，便于后续的改为递推
    def maxScore4(self, nums: List[int], x: int) -> int:
        n = len(nums)

        @lru_cache(maxsize=None)
        def f(i:int, j:int):
            if i == n:
                return 0
            if nums[i]%2 != j:
                return f(i+1, j)
            return max(f(i+1, nums[i]%2), f(i+1,nums[i]%2^1)-x)+nums[i]
        
        return max(f(0, 0), f(0, 1))
    
    def maxScore5(self, nums: List[int], x: int) -> int:
        n = len(nums)

        @lru_cache(maxsize=None)
        def f(i:int, j:int):
            if i == n:
                return 0
            
            # select
            res = f(i+1, nums[i]%2) + nums[i] - (x if j!=nums[i]%2 else 0)
            return max(f(i+1, j), res)
        
        return max(f(0, 0), f(0, 1))

if __name__ == "__main__":
    sol = Solution()
    # 按题意返回470,若第一个元素可选可不选的最大值为486
    nums = [8,50,65,85,8,73,55,50,29,95,5,68,52,79]
    print(sol.maxScore3(nums, 74))
    print(sol.maxScore5(nums, 74))