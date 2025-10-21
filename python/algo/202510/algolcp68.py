from collections import defaultdict
from typing import List

# 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution:
    def beautifulBouquet(self, flowers: List[int], cnt: int) -> int:
        l = ans = 0
        f_tot = defaultdict(int)
        for r, f in enumerate(flowers):
            f_tot[f] += 1
            while f_tot[f] > cnt:
                f_tot[flowers[l]] -= 1
                l += 1
            ans += r - l + 1
        return ans