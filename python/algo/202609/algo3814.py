from bisect import bisect_right
from typing import List


class Solution:
    def maxCapacity(self, costs: List[int], capacity: List[int], budget: int) -> int:
        # 单调栈 costs capacity 递增
        st = []

        ans = 0
        for cost, cap in sorted(zip(costs, capacity)): # 按照 cost 递增排序
            if cost < budget and cap > ans : ans = cap
            if not st:
                st.append((cost, cap))
                continue
            idx = bisect_right(st, (budget-cost, 0))    # 找到符合 cost 要求的最大容量
            if idx: ans = max(ans, cap + st[idx-1][1])

            if cap > st[-1][1]: # cost 递增，cap 必须大于栈顶元素的容量
                st.append((cost, cap))

        return ans