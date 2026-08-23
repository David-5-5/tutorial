from collections import defaultdict
from typing import List


class Solution:
    def numOfPairs(self, nums: List[str], target: str) -> int:
        pre_cnt, suf_cnt = defaultdict(int), defaultdict(int)

        ans, n = 0, len(target)
        for num in nums:
            m = len(num)
            if (m >= n) : continue
            if num == target[n-m:]:
                ans += pre_cnt[target[0:n-m]]
            if num == target[0:m]:
                ans += suf_cnt[target[m:]]
            if num == target[n-m:]:
                suf_cnt[num] += 1
            if num == target[0:m]:
                pre_cnt[num] += 1

        return ans

if __name__ == "__main__":
    nums = ["777","7","77","77"]
    target = "7777"
    Solution().numOfPairs(nums, target)