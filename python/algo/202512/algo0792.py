from bisect import bisect_right
from typing import List

# 九、子序列自动机
class Solution:
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        # 参考题解
        pos = [[] for _ in range(26)]

        for i, ch in enumerate(s):
            pos[ord(ch)-ord('a')].append(i)
        
        print(pos)
        ans = 0
        for word in words:
            start = -1
            satisfied = True
            for ch in word:
                inx = bisect_right(pos[ord(ch)-ord('a')], start)
                if inx == len(pos[ord(ch)-ord('a')]):
                    satisfied = False
                    break
                else: start = pos[ord(ch)-ord('a')][inx]

            if satisfied: ans += 1
        
        return ans