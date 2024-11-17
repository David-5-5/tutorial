from math import inf
from typing import List

# 周赛 368
class Solution:
    def minimumSum(self, nums: List[int]) -> int:
        n = len(nums)
        suf_mx = [0] * n
        suf_mx[-1] = nums[-1]

        # 计算后缀最小值
        for i in range(n-2, -1, -1):
            suf_mx[i] = min(nums[i], suf_mx[i+1])
        
        ans, pre_mx = inf, nums[0]
        for i in range(1,n-1):
            if nums[i] > pre_mx and nums[i] > suf_mx[i+1]:
                ans = min(ans, nums[i] + pre_mx + suf_mx[i+1])
            # 更新前缀最小值
            if pre_mx > nums[i]: pre_mx = nums[i]
        return ans if ans < inf else -1

if __name__ == "__main__":
    sol = Solution()
    nums = [5,4,8,7,10,2]
    print(sol.minimumSum(nums))