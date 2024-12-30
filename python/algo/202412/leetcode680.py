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
                return check(i+1,j) or check(i,j-1)
            else:
                return False
        return check(0, len(s)-1)

    def validPalindrome2(self, s: str) -> bool:
        # 不用递归，判断回文写两遍
        def check(i:int, j:int) -> bool:
            while i < j:
                if s[i] != s[j]:
                    return False
                else:
                    i += 1
                    j -= 1
            return True

        low, high = 0, len(s)-1
        while low < high:
            if s[low] != s[high]:
                return check(low+1, high) or check(low,high-1)
            else:
                low += 1
                high -= 1
        return True