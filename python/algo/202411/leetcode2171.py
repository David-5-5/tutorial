from itertools import accumulate
from math import inf
from typing import List

# 贪心专题 先枚举，再贪心
class Solution:
    def minimumRemoval(self, beans: List[int]) -> int:
        # 自行解答 排序后枚举
        beans.sort()
        n = len(beans)
        presum = list(accumulate(beans, initial=0))

        ans, res = inf, 0
        for i, v in enumerate(beans):
            # 以当前值为最小值需要取出的数量 = 
            #   已经清空的数量 + sum(bean[i]..beans[n-1]) - beans[i]*(n-i))
            ans = min(ans, res + presum[n] - presum[i] - v * (n-i))
            res += v # 清空当前数量

        return ans