from math import comb
from typing import List

# 3426
class Solution:
    def distanceSum(self, m: int, n: int, k: int) -> int:
        MOD = 10 ** 9 + 7
        # 固定两个点的距离
        # |xi - xj| 的组合数是 comb(m*n-2, k-2)
        # |xi - xj| 的情况是 m*m*sum(d*(n-d))=m*m*comb(n,3)  1<=d<n-1
        # y 同理
        return comb(n*m-2) % MOD (n * n * comb(n+1, 3) + m * m * comb(m+1, 3)) % MOD
        
if __name__ == "__main__":
    sol = Solution()
    print(sol)