from typing import List
from sortedcontainers import SortedList

# 常用数据结构 - 8.1 树状数组和线段树 - 树状数组
class Solution:
    def createSortedArray(self, instructions: List[int]) -> int:
        # 使用 SortedList 来维护有序数组，方便进行二分查找
        mod = 10**9 + 7
        sl = SortedList()
        ans = 0
        for v in instructions:
            left = sl.bisect_left(v)  # 严格小于 v 的数的个数
            right = len(sl) - sl.bisect_right(v)  # 严格大于 v 的数的个数
            ans = (ans + min(left, right)) % mod
            sl.add(v)
        return ans