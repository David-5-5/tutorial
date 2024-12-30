# 贪心专题 - 回文串贪心

class Solution:
    def breakPalindrome(self, palindrome: str) -> str:
        # 自行解答
        if len(palindrome) == 1: return ""

        n = len(palindrome)
        ls = list(palindrome)
        for i in range(n//2):
            if ls[i] != 'a':
                ls[i] = 'a'
                return "".join(ls)
        ls[n-1] = 'b' # 前面全是 a,将最后 a 修改为 b
        return "".join(ls)        