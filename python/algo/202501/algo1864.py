# 贪心专题 - 其他
class Solution:
    def minSwaps(self, s: str) -> int:
        cnt = s.count("1")
        if len(s) == cnt * 2:
            ans = sum(1 if ch1!=ch2 else 0 for ch1, ch2 in zip(s, ['0', '1'] * cnt)) // 2 # 0,1 一样多
            ans = min(ans, sum(1 if ch1!=ch2 else 0 for ch1, ch2 in zip(list(s), ['1', '0'] * cnt)) // 2)
            return ans
        elif len(s) + 1 == cnt * 2: # 1 比 0 多
            return  sum(1 if ch1!=ch2 else 0 for ch1, ch2 in zip(list(s), ['1'] + ['0', '1'] * (cnt-1))) // 2
        elif len(s) - 1 == cnt * 2:
            return  sum(1 if ch1!=ch2 else 0 for ch1, ch2 in zip(list(s), ['0'] + ['1', '0'] * cnt)) // 2
        else: return -1