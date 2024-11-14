from typing import List

# 双周赛 134
class Solution:
    def numberOfAlternatingGroups(self, colors: List[int], k: int) -> int:
        # 自行解答，滑动窗口
        n = len(colors)
        cc = colors + colors[0:n]
        
        ans = l = r = 0
        while l < n:
            if r - l + 1 == k:
                ans += 1
                l += 1
            if cc[r] != cc[r+1]:
                r += 1
            else:
                l = r = r + 1
        return ans



