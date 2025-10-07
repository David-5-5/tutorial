# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        # 自行解答 滑动窗口
        leftCost, l, ans = maxCost, 0, 0

        for r, [sr, tr] in enumerate(zip(s, t)):
            leftCost -= abs(ord(sr)-ord(tr))    # 对每个字符执行相等操作
            while leftCost < 0:                 # 保持 leftCost 非负
                leftCost += abs(ord(s[l])-ord(t[l]))
                l += 1
            ans = max(ans, r - l + 1)
        return ans        

