from math import inf


class Solution:
    def minOperations(self, s: str) -> int:
        # 暴力
        ans, n = inf, len(s)

        for j in range(n):
            res = j
            for i in range(n//2):
                l, r = ord(s[(j + i)%n]), ord(s[(-1-i+j)%n])
                res += min((l-r) % 26, (r-l) % 26)

            if ans > res: ans = res
        return ans
