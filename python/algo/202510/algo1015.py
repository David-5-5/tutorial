# 数学算法 - 数论 - 1.10 其他
class Solution:
    def smallestRepunitDivByK(self, k: int) -> int:
        # 若一个已知的超长数除以 k 的余数，可以按位 k 取余，(rem * 10 + cur) % k
        # 全是 1 的数正向反向是一样的，存在余数为零即结束
        # 异常情况，存在余数相同的情况，为循环，则不存在
        rems = set()
        x = 1 % k   # 当前余数为 1
        while x and x not in rems:
            rems.add(x)
            x = (x*10 + 1) % k

        return -1 if x else len(rems) + 1
