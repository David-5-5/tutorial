class Solution:
    def beautySum(self, s: str) -> int:
        n, ans = len(s), 0

        for i in range(n):
            cnt = [0] * 26
            for j in range(i, n):
                cnt[ord(s[j]) - ord('a')] += 1
                mn, mx = n + 1, 0
                for c in cnt:
                    if c and c < mn: mn = c
                    if c > mx: mx = c
                ans += mx - mn
        return ans