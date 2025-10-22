# 数学算法 - 组合数学 - 2.2 组合计数
class Solution:
    def countOrders(self, n: int) -> int:
        # 自行解答，(2*n)!/2^n 逆元计算
        # 每对元素的位置固定 Pi 在 Di前，因此对每对元素除以2，n 对元素共需要 2^n
        mod = 10 ** 9 + 7
        perm = 1
        for i in range(1, 2*n+1):
            perm = (perm * i) % mod
        
        return (perm * pow(pow(2, n, mod),-1, mod)) % mod