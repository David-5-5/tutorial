from typing import List

# 位运算 - 基础题
class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        a, b = 0, 0
        ans = []
        for i, j in zip(A, B):
            a |= 1 << i
            b |= 1 << j
            ans.append((a&b).bit_count())
        return ans