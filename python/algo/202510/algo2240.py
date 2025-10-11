# 数学算法 - 数论 - 1.10 其他
class Solution:
    def waysToBuyPensPencils(self, total: int, cost1: int, cost2: int) -> int:
        # 参考题解 - 按照题意模拟
        ans = 0
        for sp in range(0, total+1, cost1):
            ans += (total-sp)//cost2 + 1
        return ans