from cmath import inf
from typing import List

# 周赛 400
class Solution:
    def minimumDifference(self, nums: List[int], k: int) -> int:
        # 参考题解， logTrick
        ans = inf
        for i, v in enumerate(nums):
            ans = min(ans, abs(k-nums[i]))
            for j in range(i-1, -1, -1):
                if nums[j] == nums[j] | v:
                    break
                nums[j] |= v
                ans = min(ans, abs(k-nums[j]))
        return ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [8,89,23,12,13], 59
    print(sol.minimumDifference(nums, k))