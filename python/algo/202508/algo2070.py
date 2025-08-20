from typing import List

# 常用数据结构 - 专题 - 离线算法
class Solution:
    def maximumBeauty(self, items: List[List[int]], queries: List[int]) -> List[int]:
        items.sort()
        l, n, mx = 0, len(items), 0
        ans = [0] * len(queries)

        for i, v in sorted(enumerate(queries), key=lambda p: p[1]):
            while l < n and items[l][0] <= v:
                mx = max(mx, items[l][1])
                l += 1
            ans[i] = mx

        return ans