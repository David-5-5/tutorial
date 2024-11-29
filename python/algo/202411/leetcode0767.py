from typing import Counter

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def reorganizeString(self, s: str) -> str:
        # 参考题解
        # 方法一，构造法，按出现的频率高低，从偶数下标开始分配，然后从奇数下标分配字符
        #        当出现最多次数的字符 m <= n - m + 1总是可以保证相邻元素不同
        n = len(s)
        ans = [''] * n
        cnt = Counter(s)
        m = max(cnt.values())
        if m > n - m + 1: return ""
        i = 0
        for ch, c in sorted(cnt.items(), key=lambda p:-p[1]):
            for _ in range(c):
                ans[i] = ch
                i += 2
                if i >= n: i = 1
        return "".join(ans)