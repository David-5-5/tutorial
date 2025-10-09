# 滑动窗口与双指针 - 不定长滑动窗口 2.1.1 基础
class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        # 自行解答
        t_cnt = f_cnt = l = ans = 0
        for r, ch in enumerate(answerKey):
            if ch == 'T': t_cnt += 1
            else: f_cnt += 1
            while min(t_cnt, f_cnt) > k:
                if answerKey[l] == 'T': t_cnt -= 1
                else: f_cnt -= 1
                l += 1
            ans = max(ans, r - l + 1)
        return ans   