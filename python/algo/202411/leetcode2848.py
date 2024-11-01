from itertools import accumulate
from typing import List

# 周赛 362
class Solution:
    def numberOfPoints(self, nums: List[List[int]]) -> int:
        # 参考题解 差分数组
        n = max(max(row) for row in nums)
        diff = [0] * (n+1)
        for s, e in nums:
            diff[s] += 1
            if e + 1 <= n:
                diff[e+1] -= 1
        return sum(1 if i else 0 for i in accumulate(diff) )

if __name__ == "__main__":
    sol = Solution()
    nums = [[1,9],[2,10],[6,7],[8,9],[5,8],[1,3]]
    print(sol.numberOfPoints(nums))