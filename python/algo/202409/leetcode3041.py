from collections import defaultdict
from typing import List

# 双周赛 124
class Solution:
    def maxSelectedElements(self, nums: List[int]) -> int:
        # 参考题解
        nums.sort()
        f = defaultdict(int)
        for x in nums:
            f[x + 1] = f[x] + 1
            f[x] = f[x - 1] + 1
        return max(f.values())

if __name__ == "__main__":
    sol = Solution()
    nums = [2,1,5,1,1]
    print(sol.maxSelectedElements(nums))
