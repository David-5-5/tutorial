from typing import List


class Solution:
    def stringSequence(self, target: str) -> List[str]:
        n = len(target)
        ans = []
        seq = []

        for i in range(n):
            seq.append('`')
            d = ord(target[i]) - ord(seq[-1])
            for j in range(d):
                seq[i] = chr(ord(seq[i]) + 1)
                ans.append("".join(seq))
        return ans

