from functools import cache

class Solution:
    @cache
    def isScramble(self, s1: str, s2: str) -> bool:
        n = len(s1)
        if s1 == s2: return True
        if n == 1: return s1 == s2
        
        if sorted(s1) != sorted(s2): return False
        
        for i in range(1, n):

            if sorted(s1[0:i]) == sorted(s2[0:i]) and self.isScramble(s1[0:i], s2[0:i]) and self.isScramble(s1[i:], s2[i:]):
                return True
            if sorted(s1[0:i]) == sorted(s2[-i:]) and self.isScramble(s1[0:i], s2[-i:]) and self.isScramble(s1[i:], s2[0:n-i]):
                return True

        return False

