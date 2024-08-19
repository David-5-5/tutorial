from itertools import accumulate
from typing import List

# 双周赛 104

# 将 nums 排序后从 1 到 n，增量计算英雄值
# hero[1] = nums[1]^3
# hero[2] = nums[1]^3 + nums[2]^3 + nums[1] * nums[2]^2
#         = here[1] + nums[2]^3 + nums[1] * nums[2]^2
# hero[3] = here[3] + nums[3]^3 + (2 * nums[1] + nums[2] ) * nums[3]^2
# hero[4] = here[4] + nums[4]^3 + (4 * nums[1] + 2*nums[2] + nums[3] ) * nums[4]^2
# hero[5] = here[5] + nums[5]^3 + (8 * nums[1] + 4*nums[2] + 2 * nums[3] + nums[4] ) * nums[5]^2
#  ...          ...         ...
# hero[i] = here[i] + nums[i]^3 + (2^(i-2) * nums[1] + 2^(i-3)*nums[2] + ... + 2^0 * nums[i-1] ) * nums[i]^2
# 
# 对于 i 计算增量, 括号内的和定义为 eoff_i 为 2^(i-2)*nums[1] + 2^(i-3)*nums[2] + 2^0 * num[i-1]
# 因此计算 i+1 时，eoff_i+1 = eoff_i * 2 + num[i], O(1) 时间复杂度更新系数
class Solution:
    def sumOfPower(self, nums: List[int]) -> int:
        MOD = 10 ** 9 + 7
        nums.sort()
        hero = eoff = 0
        for i, num in enumerate(nums):
            eoff = (eoff * 2 + nums[i-1] if i else 0) % MOD
            hero = (hero + (num ** 3) + eoff * (num ** 2)) % MOD
        return hero

if __name__ == "__main__":
    sol = Solution()
    nums = [2,1,4,3,5]
    print(sol.sumOfPower(nums))