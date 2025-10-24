from collections import defaultdict
from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.3.2 越长越合法
class Solution:
    def countGood(self, nums: List[int], k: int) -> int:
        # 自行解答
        cnt = defaultdict(int)
        l = ans = cv = 0

        for v in nums:
            cnt[v] += 1
            cv += cnt[v]-1
            while cv >= k:
                cnt[nums[l]] -= 1
                cv -= cnt[nums[l]]
                l += 1
            ans += l
        return ans