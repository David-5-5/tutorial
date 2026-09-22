class Solution:
    def countSubstrings(self, s: str, t: str) -> int:
        m, n, ans = len(s), len(t), 0

        for i in range(m):
            for j in range(n):
                cnt, l = 0, 0
                while i + l < m and j + l < n:
                    if s[i + l] != t[j + l]:
                        cnt += 1
                    if cnt == 1: ans += 1
                    elif cnt > 1: break
                    l += 1
        return ans
