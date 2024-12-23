from typing import List

# 贪心专题 - 字典序最小/最大
class Solution:
    def nearestPalindromic(self, n: str) -> str:
        # 自行解答
        if int(n) <= 10: return str(int(n) - 1)
        if n == '11': return '9'
        def isPalindrome(n:List[str]) -> bool:
            m = len(n)
            for l in range(m//2):
                if n[l] != n[m-l-1]: return False
            return True

        def nearest(n: str) -> tuple[int,int]:
            mid = (len(n) + 1) // 2
            inc1 = str(int(n[0:mid]) + 1)
            sub1 = str(int(n[0:mid]) - 1)
            inc1 += inc1[::-1][len(n)%2 if len(inc1)==mid else len(n)%2+1:]
            if len(sub1) == mid:
                sub1 += sub1[::-1][len(n)%2:]
            else:
                if len(n)%2:
                    sub1 += sub1
                else: sub1 = sub1 + '9' + sub1

            return int(inc1), int(sub1)


        if not isPalindrome(n):
            l_n = list(n)
            for l in range(len(n) //2):
                if l_n[l] != l_n[len(n)-l-1]:
                    l_n[len(n)-l-1] = n[l]
            p_n = "".join(l_n)
            inc1, sub1 = nearest(p_n)
            mn = min(abs(sub1-int(n)),abs(inc1-int(n)), abs(int(p_n)-int(n)))
            if abs(sub1 - int(n)) == mn:
                return str(sub1)
            elif abs(int(p_n)-int(n)) == mn:
                return p_n
            else: return str(inc1)
        else:
            inc1, sub1 = nearest(n)

            if int(n) - sub1 <= inc1 - int(n):
                return str(sub1)
            else: return str(inc1)