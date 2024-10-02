from math import inf
from typing import List

# 双周赛 127
class Solution:
    def minimumSubarrayLength(self, nums: List[int], k: int) -> int:
        cnt = [0] * 31
        l = or_sum = 0
        ans = inf
        for r, num in enumerate(nums):
            
            bit_i = 0
            while num:
                if num & 1:
                    if cnt[bit_i] == 0: or_sum += pow(2, bit_i)
                    cnt[bit_i] += 1
                bit_i += 1
                num >>= 1
            
            while or_sum >= k and l <= r:
                ans = min(ans, r-l+1)
                out = nums[l]
                bit_i = 0
                while out:
                    if out & 1:
                        cnt[bit_i] -= 1
                        if cnt[bit_i] == 0: or_sum -= pow(2, bit_i)
                    bit_i += 1
                    out >>= 1
                l += 1
        return -1 if ans == inf else ans
    
if __name__ == "__main__":
    sol = Solution()
    nums, k = [1,2,3], 2
    nums, k = [1,2,32,21], 55
    print(sol.minimumSubarrayLength(nums, k))