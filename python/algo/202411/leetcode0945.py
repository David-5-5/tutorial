from typing import List

# 贪心专题
class Solution:
    def minIncrementForUnique(self, nums: List[int]) -> int:
        # 自行解答
        nums.sort()
        ans, cur = 0, nums[0]
        for v in nums:
            if v < cur: ans += cur - v
            cur = max(v, cur) + 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,1,2,1,7]
    print(sol.minIncrementForUnique(nums))