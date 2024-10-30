from collections import defaultdict
from itertools import accumulate
from typing import List

# 周赛 361
class Solution:
    def countInterestingSubarrays(self, nums: List[int], modulo: int, k: int) -> int:
        # 参考题解
        # 总结，思路也是围绕类似两数之和的哈希算法，但是技巧没有把握
        # 1, 前缀和计算，将 nums[i] % modulo == k 设置为 1 ，其他设置为 0
        # 2, Hash 计数技巧 (nums[i]-k)%modulo 查找前缀和的计数
        c_nums = [1 if i % modulo == k else 0 for i in nums]
        cnt = defaultdict(int)
        
        pre_c = list(accumulate(c_nums, initial=0))
        ans = 0

        for v in pre_c:
            ans += cnt[(v-k)%modulo] # 才开始写成(v+k)%modulo
            cnt[(v)%modulo] += 1

        return ans

if __name__ == "__main__":
    sol = Solution()
    nums, modulo, k = [3,2,4], 2, 1
    nums, modulo, k = [3,1,9,6], 3, 0
    print(sol.countInterestingSubarrays(nums, modulo, k))

        