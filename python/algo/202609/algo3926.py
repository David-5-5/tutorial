from typing import Counter


class Solution:
    def countWordOccurrences(self, chunks: list[str], queries: list[str]) -> list[int]:
        s = list("".join(chunks))
        n = len(s)
        for i in range(n):
            if s[i] == '-' and (i == 0 or s[i-1]<'a' or s[i-1]>'z' or \
                i == n-1  or s[i+1]<'a' or s[i+1]>'z'):
                s[i] = ' '

        chunks = "".join(s).split(" ")
        cnt = Counter(chunks)
        m = len(queries)
        ans = [0] * m
        for i, q in enumerate(queries):
            ans[i] = cnt[q]
        return ans