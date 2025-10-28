from math import lcm

# 数学算法 - 组合数学 - 2.4 容斥原理
class Solution:
    def nthUglyNumber(self, n: int, a: int, b: int, c: int) -> int:
        # 自行解答
        ab, bc, ac,= lcm(a, b), lcm(b, c), lcm(a, c) 
        abc = lcm(a, bc)

        def check(mid):
            count = mid // a + mid // b + mid // c
            count -= mid // ab + mid // bc + mid // ac
            count += mid // abc
            return count >= n
        
        left = min(a, b, c) - 1
        right = abc * n
        
        while left + 1 < right:
            mid = (left + right) // 2
            if check(mid): right = mid
            else: left = mid
        
        a_cnt, b_cnt, c_cnt, ab_cnt = right // a, right // b, right // c, right // ab
        bc_cnt, ac_cnt, abc_cnt= right // bc, right // ac, right // abc

        return max(a_cnt * a, b_cnt * b, c_cnt * c, 
                   ab_cnt * ab, bc_cnt * bc, ac_cnt * ac, abc_cnt * abc)