from typing import List, Tuple

MX = 10 ** 4 + 1
lpf = [0] * MX
for i in range(2, MX):
    if lpf[i] == 0:  # i 是质数
        for j in range(i, MX, i):
            if lpf[j] == 0:  # 首次访问 j
                lpf[j] = i

# 质因数分解
# 例如 prime_factorization(45) = [(3, 2), (5, 1)]，表示 45 = 3**2 * 5**1
# 时间复杂度 O(log x)
def prime_factors(x: int) -> List[Tuple[int, int]]:
    res = []
    while x > 1:
        p = lpf[x]
        e = 1
        x //= p
        while x % p == 0:
            e += 1
            x //= p
        res.append((p, e))
    return res

MOD = 10 ** 9 + 7
MAX_K = 14
MAX_N = MX+MAX_K
# 计算组合数 - 动态规划 C(n, k) = C(n-1,k-1) + c(n-1, k)  选或不选
C = [[0] * MAX_K for _ in range(MAX_N)]
for i in range(MAX_N):
    for j in range(1, min(MAX_K, i+1)):
        C[i][0] = 1
        C[i][j]= (C[i-1][j-1] + C[i-1][j]) % MOD

#  数学算法 - 数论 - 1.3 质因数分解
class Solution:
    def waysToFillArray(self, queries: List[List[int]]) -> List[int]:
        # 参考题解，本题 k 的范围为 14, 10000 的因式分解 10000 < 2^14
        ans = [0] * len(queries)

        for i, [n, comp] in enumerate(queries):
            tot = 1
            for _, k in prime_factors(comp):
                tot = (tot * C[k+n][k]) % MOD
            ans[i] = tot
        return ans

        
