from string import ascii_lowercase
from typing import Counter


class Solution:
    def lengthAfterTransformations(self, s: str, t: int) -> int:
        cnt = Counter(s)
        cnt2 = Counter()
        MOD = 10 ** 9 + 7
        expo = t // 26
        for _ in range(expo):
            for ch in ascii_lowercase:
                if ch == 'z':
                    # cnt2['z'] += cnt['z']
                    cnt2['a'] = (cnt['a'] + cnt[ch]) % MOD
                    cnt2['b'] = (cnt['b'] + cnt[ch]) % MOD
                else:
                    nx = chr(ord(ch)+1)
                    cnt2[nx] = (cnt[nx] + cnt[ch]) % MOD
            cnt = cnt2
            cnt2 = Counter()
        
        rem = t % 26
        for _ in range(rem):
            for ch in ascii_lowercase:
                if ch == 'z':
                    cnt2['a'] += cnt['z'] 
                    cnt2['b'] += cnt['z']
                else:
                    nx = chr(ord(ch)+1)
                    cnt2[nx] = cnt[ch] % MOD
            cnt = cnt2
            cnt2 = Counter()
        
        return sum(i for i in cnt.values()) % MOD       

if __name__ == "__main__":
    sol = Solution()
    s, t = "abcyy", 2
    s, t = "jqktcurgdvlibczdsvnsg", 52
    print(sol.lengthAfterTransformations(s, t))