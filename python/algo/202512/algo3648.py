# 数学算法 7.7 其他
class Solution:
    def minSensors(self, n: int, m: int, k: int) -> int:
        side = k * 2 + 1
        return ((n + side-1) // side) * ((m + side -1) // side)