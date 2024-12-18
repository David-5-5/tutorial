from typing import List

# 贪心专题 - 合并区间
class Solution:
    def numberOfGoodPartitions(self, nums: List[int]) -> int:
        int_h = {}

        for i, v in enumerate(nums):
            if v in int_h:
                int_h[v][1] = i
            else:int_h[v] = [i,i]
        
        intervals = list(int_h.values())
        # 以下是 0056 区间合并代码
        intervals.sort()
        ans = []
        left, right = intervals[0]
        for l, r in intervals[1:]:
            if l > right:
                ans.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        ans.append([left, right])
        # 以上是 0056 区间合并代码

        return pow(2, len(ans)-1, 10**9+7)