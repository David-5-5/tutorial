from typing import List

# 贪心专题 - 不相交区间
class Solution:
    def findLongestChain(self, pairs: List[List[int]]) -> int:
        # 自行解答
        pairs.sort(key=lambda p:p[1]) # 按右端点排序
        # 因为右端点尽量小，才能有 后续的pair 的左端点 > 当前的右端点

        right = pairs[0][1]
        ans = 1
        for l, r in pairs[1:]:
            if l > right:
                ans += 1
                right = r
        return ans


