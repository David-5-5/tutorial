# 滑动窗口与双指针 - 求子数组个数 2.3.1 越短越合法
class Solution:
    def countKConstraintSubstrings(self, s: str, k: int) -> int:
        # 自行解答
        l = ans = cnt0 = cnt1 = 0
        for r, ch in enumerate(s):
            if ch == '1': cnt1 += 1
            else: cnt0 += 1
            while cnt0 > k and cnt1 > k:
                if s[l] == '1': cnt1 -= 1
                else: cnt0 -= 1
                l += 1
            ans += r - l + 1
        return ans