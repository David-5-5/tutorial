# 数学算法 - 组合数学 - 2.2 组合计数
from math import comb


class Solution:
    def valueAfterKSeconds(self, n: int, k: int) -> int:
        # 暴力 O(km)
        mod = 10 ** 9 + 7
        nums = [1] * n
        for _ in range(k):
            for i in range(1, n):
                nums[i] = (nums[i] + nums[i-1]) % mod
        return nums[-1]

    def valueAfterKSeconds(self, n: int, k: int) -> int:
        # 帕斯卡三角，计算第 n+k-1 的第 k 个数 c(n+k-1, k)
        return comb(n+k-1, k) % (10 ** 9 + 7)