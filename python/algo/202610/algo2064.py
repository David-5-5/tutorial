from typing import List


class Solution:
    def minimizedMaximum(self, n: int, quantities: List[int]) -> int:
        q_sum = sum(quantities)

        def check(limit: int) -> bool:
            m = 0
            for q in quantities:
                m += (q + limit -1) // limit
            
            if m <= n: return True
            else: False
        
        l, r = 0, q_sum + 1
        while l + 1 < r:
            mid = (l + r) // 2
            if check(mid):
                r = mid
            else: l = mid
        return r