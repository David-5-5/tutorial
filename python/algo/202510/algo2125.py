from typing import List

# 数学算法 - 组合数学 - 2.1 乘法原理
class Solution:
    def numberOfBeams(self, bank: List[str]) -> int:
        ans = prev = 0
        for r in bank:
            cur = r.count('1')
            ans += cur * prev
            if cur: prev = cur
        return ans