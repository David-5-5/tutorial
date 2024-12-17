from ast import List

# 贪心专题 - 归纳法
class Solution:
    def getMaximumConsecutive(self, coins: List[int]) -> int:
        x = 1
        for v in sorted(coins):
            if v <= x:
                x += v
            else:
                break # return x
        return x