from math import comb
from typing import List

# 周赛 374 
class Solution:
    def numberOfSequence(self, n: int, sick: List[int]) -> int:
        # 参考题解 数学组合 算法
        # 两个感染的区间为排序数为： 2^(m-1) m 为两个区间中未感染数量
        # 对于两个只有一个感染的区间排序数为 1
        # 对于多个区间 m = m_1 m_2 ... m_k-1, m_k
        #   排序数为C(m,m1)*C(m2,m-m1)*...*C(mk,m-m_1-...-m_k-1) * 2^(m-k)
        MOD = 10 ** 9 + 7

        sub = 0
        if sick[0] != 0:
            sub += sick[0]
            sick.insert(0,-1)
        if sick[-1] != n-1:
            sub += n - sick[-1] - 1
            sick.append(n)

        seg = []
        for l, r in zip(sick,sick[1:]):
            seg.append(r-l-1)

        m = sum(seg)
        ans = pow(2, m-len(seg), MOD) if sub == 0 else pow(2, m-len(seg)-sub+2, MOD)

        for i in seg:
            ans = ans * comb(m, i) % MOD
            m -= i
        return ans

