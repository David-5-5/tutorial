from functools import cache

# LCR series 同 233
class Solution:
    def digitOneInNumber(self, num: int) -> int:
        s = str(num)

        @cache
        def f(i: int, cnt1: int, is_limit: bool) -> int:
            if i == len(s):
                return cnt1
            res = 0
            up = int(s[i]) if is_limit else 9
            for d in range(up + 1):  # 枚举要填入的数字 d
                res += f(i + 1, cnt1 + (d == 1), is_limit and d == up)
            return res
        return f(0, 0, True)