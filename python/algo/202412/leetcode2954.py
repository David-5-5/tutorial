from typing import List

MOD = 1_000_000_007
MX = 100_000

# 组合数模板 组合数 求 逆元 
# replace math.comb
fac = [0] * MX
fac[0] = 1
for i in range(1, MX):
    fac[i] = fac[i - 1] * i % MOD

inv_fac = [0] * MX
inv_fac[MX - 1] = pow(fac[MX - 1], -1, MOD)
for i in range(MX - 1, 0, -1):
    inv_fac[i - 1] = inv_fac[i] * i % MOD

def comb(n: int, k: int) -> int:
    return fac[n] * inv_fac[k] % MOD * inv_fac[n - k] % MOD


# 周赛 374 
class Solution:
    def numberOfSequence(self, n: int, sick: List[int]) -> int:
        # 参考题解 数学组合 算法
        # 两个感染的区间为排序数为： 2^(m-1) m 为两个区间中未感染数量
        # 对于两个只有一个感染的区间排序数为 1
        # 对于多个区间 m = m_1 m_2 ... m_k-1, m_k
        #   排序数为C(m,m1)*C(m2,m-m1)*...*C(mk,m-m_1-...-m_k-1) * 2^(m-k)
    
        sub = 0
        if sick[0] != 0:
            sub += sick[0] - 1
            sick.insert(0,-1)
        if sick[-1] != n-1:
            sub += n - sick[-1] - 2
            sick.append(n)

        seg = []
        for l, r in zip(sick,sick[1:]):
            if r-l-1:seg.append(r-l-1)

        m = sum(seg)
        ans = pow(2, m-len(seg), MOD) if sub == 0 else pow(2, m-len(seg)-sub, MOD)

        for i in seg:
            ans = ans * comb(m, i) % MOD
            m -= i
        return ans