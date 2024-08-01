from itertools import accumulate
from typing import List


class Solution:

    def productQueries(self, n: int, queries: List[List[int]]) -> List[int]:
        MOD = 10 ** 9 + 7
        powers = []
        # 步骤一：分解 n 的 2 的幂数组
        # 方法一：移位检查
        for i in range(32): # 10 ** 9
            if (n >> i) & 1 == 1:
                powers.append(i)
                # powers.append(pow(2, i, MOD))
        
        # 方法二：lowbit
        # while n:
        #     lowbit = n & -n
        #     powers.append(lowbit)
        #     n ^= lowbit

        # ans = []
        # 步骤二：按 queries 计算结果
        # 方法一暴力计算 时间复杂度 O(lgN*M)
        # for l, r in queries:
        #     res = 1
        #     for i in range(l, r+1):
        #         res = res * powers[i] % MOD
        #     ans.append(res)
        
        # 方法二 打表 时间复杂度 O((lgN)^2 + M)
        # res = [[powers[i]] * len(powers)  for i in range(len(powers))]
        # for i in range(len(powers)):
        #     for j in range(i+1, len(powers)):
        #         res[i][j] = res[i][j-1] * powers[j] % MOD
        
        # for l, r in queries:
        #     ans.append(res[l][r])

        # 方法三 指数前缀和
        presum = list(accumulate(powers, initial=0))
    
        return [pow(2, presum[r+1]-presum[l], MOD) for l, r in queries]