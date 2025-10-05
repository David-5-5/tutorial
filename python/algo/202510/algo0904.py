from collections import defaultdict
from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        # 自行解答 滑动窗口
        f_cnt = defaultdict(int)
        l, ans = 0, 0
        for r, f in enumerate(fruits):
            f_cnt[f] += 1
            while len(f_cnt) > 2:
                f_cnt[fruits[l]] -= 1
                if f_cnt[fruits[l]] == 0:
                    del f_cnt[fruits[l]]
                l += 1
            ans = max(ans, r - l  + 1)
        return ans
                
