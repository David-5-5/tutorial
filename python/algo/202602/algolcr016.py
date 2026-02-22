from collections import defaultdict

# 同 3
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        begin = 0
        maxSubLen = 0
        for i in range(len(s)):
            index = s[begin:i].find(s[i])
            if index == -1:
                maxSubLen = max(maxSubLen, i-begin+1)
            else:
                begin = begin + index + 1    
        return maxSubLen

    def lengthOfLongestSubstring2(self, s: str) -> int:
        # 滑动窗口
        cnt = defaultdict(int)
        l, r, n, ans = 0, 0, len(s), 0
        while r < n:
            cnt[s[r]] += 1
            while cnt[s[r]] > 1:
                cnt[s[l]] -= 1
                l += 1
            if r - l + 1 > ans: ans = r - l + 1
            r += 1
        return ans