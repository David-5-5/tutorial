from math import gcd
from typing import Counter, List

# 贪心专题 - 思维题 - 从特殊到一般
class Solution:
    def minimumArrayLength(self, nums: List[int]) -> int:
        # 自行解答
        # 计算 nums 的最大公约数及其数量
        g = gcd(*nums)
        cnt = Counter(nums)

        ans = (cnt[g]+1) // 2 # 上取整
        return ans if ans!=0 else 1