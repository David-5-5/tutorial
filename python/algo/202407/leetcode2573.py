from string import ascii_lowercase
from typing import List

class Solution:
    def findTheString(self, lcp: List[List[int]]) -> str:
        n = len(lcp)
        s = [''] * n

        c = 'a'
        for i in range(n):
            if s[i] == '':
                s[i] = c
                c = chr((ord(c) - ord('a') + 1)%26 + ord('a'))
            for j in range(i+1, n):
                if lcp[i][j]:
                    s[j] = s[i]

        if '' in s: return ""

        for i in range(n):
            for j in range(i, n):
                if i == j and lcp[i][j] != n-i: # 对角线的值必须为 n - i
                    return ""
                elif i != j and lcp[i][j] != lcp[j][i]: # 必须对称
                    return ""
                
                if s[i] == s[j] and lcp[i][j] != (lcp[i+1][j+1] if i+1<n and j+1 <n else 0)  + 1:
                    return ""
                elif s[i] != s[j] and lcp[i][j] != 0:
                    return ""
    
        return ''.join(s)

if __name__ == "__main__":
    sol = Solution()
    lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
    lcp = [[3, 0, 2], [0, 2, 1], [2, 1, 1]]
    lcp = [[3, 0, 1], [0, 2, 1], [1, 1, 1]]
    print(sol.findTheString(lcp))