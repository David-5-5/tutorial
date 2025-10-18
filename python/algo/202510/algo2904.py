# 滑动窗口与双指针 - 不定长滑动窗口 2.2 越长越合法/求最短/最小
class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        # 自行解答
        if s.count('1') < k: return ""
        ans, l, cnt = s, 0, 0

        for r, ch in enumerate(s):
            if ch == '1': cnt += 1
            while l < len(s) and s[l] == '0':
                l += 1
            if cnt == k:
                if len(ans) > r - l + 1:
                    ans = s[l:r+1]
                elif len(ans) == r-l+1 and ans > s[l:r+1]:
                    ans = s[l:r+1]
                l += 1
                cnt -= 1
        return ans        