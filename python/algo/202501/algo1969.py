# 贪心专题 - 基本不等式
class Solution:
    def minNonZeroProduct(self, p: int) -> int:
        # 自行解答，数学，将大于的数两两匹配，
        # 将高位的 1 都移到大数上，小数为 1，大数为 2^p -2 
        MOD = 1_000_000_007

        # pow(2,p-1)-1 幂次不能取模
        # 使用 python pow 函数实现快速幂
        return pow(pow(2,p, MOD)-2, pow(2,p-1)-1, MOD) * (pow(2,p, MOD)-1) % MOD