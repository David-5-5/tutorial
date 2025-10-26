from typing import List

# 滑动窗口与双指针 - 不定长滑动窗口 2.3.2 越长越合法
class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        # 自行解答
        ans = l = cnt_a = cnt_b = cnt_c = 0
        for ch in s:
            if ch == 'a': cnt_a += 1
            elif ch == 'b': cnt_b += 1
            else: cnt_c += 1

            while cnt_a >= 1 and cnt_b >= 1 and cnt_c >= 1:
                if s[l] == 'a': cnt_a -= 1
                elif s[l] == 'b': cnt_b -= 1
                else: cnt_c -= 1
            
                l += 1
            ans += l
        return ans