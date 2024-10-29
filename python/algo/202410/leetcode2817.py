from math import inf
from typing import List
from sortedcontainers import SortedList

# 周赛 358
class Solution:
    def minAbsoluteDifference(self, nums: List[int], x: int) -> int:
        # 参考题解 双指针 前一个指针遍历数据排序，
        # 后一个指针在排序数组中检索并计算最小值
        s = SortedList([-inf, inf]) # 首尾增加两个哨兵，不需要判断数组越界
        ans = inf
        for x, y in zip(nums, nums[x:]):
            s.add(x) # Add value to sorted list
            inx = s.bisect_left(y)
            ans = min(ans, s[inx]-y, y - s[inx-1])
        return ans        

        