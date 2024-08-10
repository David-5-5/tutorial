import math
from typing import List

# 双周赛 84 贪婪算法
class Solution:
    def minimumReplacement(self, nums: List[int]) -> int:
        ans = 0

        limit = nums[-1]
        for v in reversed(nums):
            x = math.ceil(v/limit) # 拆分的最小数
            ans += x - 1
            limit = math.floor(v/x) # 更新上限
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums = [3,9,3]
    print(sol.minimumReplacement(nums))