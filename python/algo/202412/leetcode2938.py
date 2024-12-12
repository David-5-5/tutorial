# 周赛 372
class Solution:
    def minimumSteps(self, s: str) -> int:
        # 自行解答
        blacks = ans = 0
        for c in s:
            if c == '1': blacks += 1
            if c == '0': ans += blacks
        return ans

