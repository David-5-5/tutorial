from math import inf
from typing import List

# 贪心专题
class Solution:
    def maximumTotalSum(self, maximumHeight: List[int]) -> int:
        # 自行解答
        height, ans = inf, 0
        for h in sorted(maximumHeight, reverse=True):
            height = min(height, h)
            if height == 0: return -1

            ans += height
            height -= 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    print(sol.maximumTotalSum([2,3,4,3]))