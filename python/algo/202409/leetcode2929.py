import math


class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        # 组合数学 - 容斥原理
        # 所有方案数 - 不符合方案数
        # 所有方案数 C(n+2,2) 插板法
        # 其中不符合方案数：
        # - 集合 A 甲  超过 limit 的方案数, 即 甲分配 limit + 1个，剩余在三人中分配
        #                                   C(n+2-(limit+1),2) 插板法
        # - 集合 B 乙  超过 limit 的方案数
        # - 集合 C 丙  超过 limit 的方案数
        # - 集合 A ∩ B  同理               C(n+2-2*(limit+1),2)
        # - 集合 B ∩ C
        # - 集合 A ∩ C
        # - 集合 A ∩ B ∩ C C(n+2-3*(limit+1),2)
        # 由于集合有交集，按容斥原理不合格方案数
        # A + B + C - A ∩ B - B ∩ C - A ∩ C + A ∩ B ∩ C
        def comb(n:int) -> int:
            return math.comb(n, 2) if n else 0
    
        return comb(n+2) - 3 * comb(n+2-limit-1) + 3 * comb(n+2-2*(limit+1)) - comb(n+2-3*(limit+1))