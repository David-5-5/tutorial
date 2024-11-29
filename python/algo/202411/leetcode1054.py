from collections import Counter
from typing import List

# 贪心专题 相邻不同 证明/构造方案
class Solution:
    def rearrangeBarcodes(self, barcodes: List[int]) -> List[int]:
        # 自行解答 同 767
        n = len(barcodes)
        ans = [0] * n
        cnt = Counter(barcodes)

        i = 0
        for ch, c in sorted(cnt.items(), key=lambda p:-p[1]):
            for _ in range(c):
                ans[i] = ch
                i += 2
                if i >= n: i = 1
        return ans       