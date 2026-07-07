from cmath import inf
from collections import defaultdict
from typing import List

# 常用数据结构 -  0.1 枚举右，维护左
class Solution:
    def minMirrorPairDistance(self, nums: List[int]) -> int:
        # 自行解答，仔细读题
        mirror = defaultdict(int)

        ans = inf
        for i, v in enumerate(nums):
            if v in mirror:
                ans = min(ans, i - mirror[v])
            mirror[int(str(v)[::-1]) ] = i
        return ans if ans < inf else -1