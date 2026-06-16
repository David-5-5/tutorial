from collections import defaultdict
from functools import cache

class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        # 自行解答
        n = len(word1)

        def cal(sub1: str, sub2: str) -> int:
            res, diff = 0, defaultdict(int)
            for w1, w2 in zip(sub1,  sub2):
                if w1 != w2:
                    res += 1
                    p = (ord(w2) - ord('a')) * 26 + ord(w1) - ord('a')
                    if diff[p]:
                        diff[p] -= 1
                        res -= 1
                    else:
                        diff[(ord(w1) - ord('a')) * 26 + ord(w2) - ord('a')] += 1
            return res
                
        @cache
        def count(start: int, end: int) -> int:
            return min(word1[start:end], word2[start:end],
                        1 + cal(word1[start:end][::-1], word2[start:end]))

        @cache
        def dfs(i: int, j: int):
            if j == n: return count(i, j)

            return min(dfs(i, j+1), count(i, j) + dfs(j, j+1))

        return dfs(0, 1)

    def minOperations2(self, word1: str, word2: str) -> int:
        n = len(word1)
        # 预处理字符编码，避免循环重复计算
        c1 = [ord(c) - ord('a') for c in word1]
        c2 = [ord(c) - ord('a') for c in word2]

        def cal(s,e,rev):
            arr, res, L = [0]*676, 0, e-s
            for i in range(L):
                b=c2[s+i]
                a=c1[s+i] if not rev else c1[e-1-i]
                if a==b: continue
                res += 1
                kr, ka = b * 26 + a, a * 26 + b
                if arr[kr]: arr[kr] -= 1; res -= 1
                else: arr[ka] += 1
            return res
                
        @cache
        def count(start: int, end: int) -> int:
            normal = cal(start, end, rev=False)
            reverse_cost = 1 + cal(start, end, rev=True)
            return min(normal, reverse_cost)

        @cache
        def dfs(i: int, j: int):
            if j == n:
                return count(i, j)
            # 两种选择：不分割，继续右扩；或者在j分割
            return min(dfs(i, j+1), count(i, j) + dfs(j, j+1))

        return dfs(0, 1)