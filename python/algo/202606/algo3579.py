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

