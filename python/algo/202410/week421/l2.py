from string import ascii_lowercase
from typing import Counter


class Solution:
    def lengthAfterTransformations(self, s: str, t: int) -> int:
        cnt = [0] * 26
        for ch in s:
            cnt[ord(ch)-ord('a')] += 1
        cnt2 = [0] * 26
        MOD = 10 ** 9 + 7

        for _ in range(t):
            for ch in range(26):
                if ch == 25:
                    cnt2[0] = cnt[25] 
                    cnt2[1] += cnt[25]
                else:
                    cnt2[ch+1] = cnt[ch] % MOD
            cnt = cnt2
            cnt2 = [0] * 26
        
        return sum(cnt) % MOD       

    def lengthAfterTransformations2(self, s: str, t: int) -> int:
        cnt = [0] * 26
        for ch in s:
            cnt[ord(ch)-ord('a')] += 1
        MOD = 10 ** 9 + 7
        
        z = 25
        for i in range(t):
            cnt[(z+1-i%26)%26]  = (cnt[(z+1-i%26)%26] + cnt[(z-i%26)%26])% MOD
        
        return sum(cnt) % MOD
    
if __name__ == "__main__":
    sol = Solution()
    s, t = "abcyy", 2
    s, t = "jqktcurgdvlibczdsvnsg", 7517
    # s, t = "abcdefghijklmnopqrstuvwxyz", 1
    print(sol.lengthAfterTransformations(s, t))
    print(sol.lengthAfterTransformations2(s, t))