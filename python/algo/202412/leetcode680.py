# 贪心专题 - 回文串贪心
from functools import cache


class Solution:
    def validPalindrome(self, s: str) -> bool:
        
        can_del = True

        @cache
        def check(i:int, j:int) -> bool:
            nonlocal can_del
            
            if i > j: return True
            
            if s[i] == s[j]:
                return check(i+1, j-1)
            elif can_del:
                can_del = False
                res1 = check(i+1,j-2) if s[i] == s[j-1] else False
                res2 = check(i+2, j-1) if s[i+1] == s[j] else False
                return res1 or res2
        return check(0, len(s)-1)

