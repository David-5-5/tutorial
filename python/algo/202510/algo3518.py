from math import comb
from string import ascii_lowercase

# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        # 参考题解
        n  = len(s) // 2
        cnt = [0] * 26
        for b in s[:n]:
            cnt[ord(b) - ord('a')] += 1

        def comb(n: int, m: int) -> int:
            m = min(m, n - m)
            res = 1
            for i in range(1, m + 1):
                res = res * (n + 1 - i) // i
                if res >= k:  # 太大了
                    return k
            return res

        # 计算长度为 sz 的字符串的排列个数
        def perm(sz: int) -> int:
            res = 1
            for c in cnt:
                if c == 0:
                    continue
                # 先从 sz 个里面选 c 个位置填当前字母
                res *= comb(sz, c)
                if res >= k:  # 太大了
                    return k
                # 从剩余位置中选位置填下一个字母
                sz -= c
            return res

        if perm(n) < k:
            return ""
        
        left = []
        for i in range(n):

            for ch in ascii_lowercase:
                if cnt[ord(ch)-ord('a')] == 0: continue
                cnt[ord(ch)-ord('a')] -= 1 # 试填法
                p = perm(n-i-1)
                if p >= k:
                    left.append(ch)
                    break
                k -= p
                cnt[ord(ch)-ord('a')] += 1
        ans = "".join(left)
        return ans + (s[n] if len(s)%2 else "") + ans[::-1]