from collections import defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.1.2 进阶（选做）
class Solution:
    def longestSemiRepetitiveSubstring(self, s: str) -> int:
        # 非暴力算法 滑动窗口，自行解答
        l = cnt = 0
        ans = 1
        for r, ch in enumerate(s):
            if r == 0: continue
            if ch == s[r-1]: cnt += 1
            while cnt > 1:
                if s[l] == s[l+1]: cnt -= 1
                l += 1
            ans = max(ans, r - l + 1)
        return ans
            