from collections import defaultdict

# 滑动窗口与双指针 - 不定长滑动窗口 2.3.2 越长越合法
class Solution:
    def numberOfSubstrings(self, s: str, k: int) -> int:
        # 自行解答
        ans = l = 0
        cnt = defaultdict(int)
        for ch in s:
            cnt[ch] += 1
            while cnt[ch] == k:
                cnt[s[l]] -= 1
                l += 1
            ans += l
        return ans