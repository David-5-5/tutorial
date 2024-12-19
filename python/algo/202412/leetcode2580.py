from typing import List

# 贪心专题 - 合并区间
class Solution:
    def countWays(self, ranges: List[List[int]]) -> int:
        # 以下是 0056 区间合并代码
        ranges.sort()
        ans = []
        left, right = ranges[0]
        for l, r in ranges[1:]:
            if l > right:
                ans.append([left, right])
                left, right = l, r
            else:
                if r > right : right = r
        ans.append([left, right])
        # 以上是 0056 区间合并代码

        return pow(2, len(ans), 10**9+7)