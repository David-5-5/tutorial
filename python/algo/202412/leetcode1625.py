# 贪心专题 - 字典序最小/最大
class Solution:
    def findLexSmallestString(self, s: str, a: int, b: int) -> str:
        # 自行解答
        n, l_s = len(s), list(s)
        
        h = set()
        for i in range(n): # n 次右移 b 位
            h.add(i*b % n) # i*b % n 为起始位置
        
        mn = s
        # 10 次位置
        for j in h: # 遍历字符串的起始位置
            for _ in range(10): # 修改奇数位置 10 次
                for inx in range(1, n, 2):
                    l_s[inx] = str((int(l_s[inx]) + a) % 10)
                s = "".join(l_s)

                if b % 2: # 若 b 为奇数，修改偶数位置 10 次
                    for _ in range(10):
                        for inx in range(0, n, 2):
                            l_s[inx] = str((int(l_s[inx]) + a) % 10)
                        s = "".join(l_s)

                        s = s[j:] + s[0:j]
                        mn = min(s, mn)
                else:
                    s = s[j:] + s[0:j]
                    mn = min(s, mn)
        return mn