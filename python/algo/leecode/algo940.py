class Solution:
    def distinctSubseqII(self, s: str) -> int:
        f = [1] * len(s)
        last = [-1] * 26
        for i in range(len(s)):
            for j in range(26):
                if last[j] != -1 :
                    f[i] = (f[i] + f[last[j]]) % (10 ** 9 + 7)
            last[ord(s[i]) - ord('a')] = i
        ans = 0
        for j in range((26)):
            if last[j] != -1 :
                ans = (ans + f[last[j]]) % (10 ** 9 + 7)
        return ans

    def distinctSubseqII2(self, s: str) -> int:
        f = [0] * 26
        for c in s:
            f[ord(c) - ord('a')] = (1 + sum(f)) % (10 ** 9 + 7)
        return sum(f) % (10 ** 9 + 7)
