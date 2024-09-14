from collections import defaultdict
from functools import cache
import math
from typing import List

# 周赛 301 
class Solution:
    def idealArrays(self, n: int, maxValue: int) -> int:
        MOD = 10 ** 9 + 7
        # 自行解答, 数位DP, 内存超出限制

        @cache
        def f(i: int, prev: int) -> int:
            if i == n and prev == maxValue: return 1
            
            res = 0
            if i == 0:
                for j in range(1, maxValue+1):
                    res += f(i+1, j)
            else:
                for j in range(1, (maxValue // prev)+1):
                    res += f(i+1, prev*j)
            
            return res % MOD
        
        return f(0, -1)
    
    def idealArrays2(self, n: int, maxValue: int) -> int:
        # 参考题解 质因子分解 排列组合
        MOD = 10 ** 9 + 7

        def decompose(val: int) -> List[int] :
            factors = []
            p = 2
            while p * p <= val:
                if val % p == 0:
                    k = 0
                    while val % p == 0:
                        val //= p
                        k += 1
                    factors.append(k)
                p += 1
            if val > 1: factors.append(1)
            return factors

        def combi(b: int, f: List[int]):
            mul = 1
            for v in f:
                mul *= math.comb(b+v-1,b-1)
            return mul
        
        res = 0
        for i in range(1, maxValue+1):
            f = decompose(i)
            res = (res + combi(n, f)) % MOD
        return res % MOD
        
if __name__ == "__main__":
    sol = Solution()
    print(sol.idealArrays2(50,6))