from typing import List


class Solution:
    def nearestPalindromic(self, n: str) -> str:

        def isPalindrome(n:List[str]) -> bool:
            m = len(n)
            for l in range(n//2):
                if n[l] != n[n-l]: return False
            return True

        if not isPalindrome(n):
            for l in range(n//2):
                if n[l] != n[n-l]:
                    n[n-l] = n[l]
            return n
        else:
            mid = (len(n) + 1) // 2
            inc1 = str(int(n[0:mid]) + 1)
            sub1 = str(int(n[0:mid]) - 1)

            inc1 += inc1[::-1][len(n)%2 if len(inc1)==mid else 1:]
            sub1 += sub1[::-1][len(n)%2 if len(sub1)==mid else 0:]

            if int(n) - int(sub1) <= int(inc1) - int(n):
                return sub1
            else: return inc1
                