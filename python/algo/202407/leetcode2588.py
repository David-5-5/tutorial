from collections import Counter
from typing import List

# 当子数组异或为 0 时，表示是漂亮子数组
# 使用异或前缀和及哈希表，统计当前异或前缀和与之前异或前缀和为 0 的数量
class Solution:
    def beautifulSubarrays(self, nums: List[int]) -> int:
        s = ans = 0
        h = Counter({0:1})
        for x in nums:
            s ^= x
            ans += h[s]
            h[s] += 1
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [4,3,1,2,4]
    print(sol.beautifulSubarrays(nums)) 