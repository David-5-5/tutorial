from math import comb
# 预处理自定义comb，优化性能
MOD = 10 ** 9 + 7
MX = 100_000

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

# 3426
class Solution:
    def distanceSum(self, m: int, n: int, k: int) -> int:
        MOD = 10 ** 9 + 7
        # 固定两个点的距离
        # |xi - xj| 的组合数是 comb(m*n-2, k-2)
        # |xi - xj| 的情况是 m*m*sum(d*(n-d))=m*m*comb(n,3)  1<=d<n-1
        # y 同理
        return comb(n*m-2, k-2) % MOD * (n * n * comb(m+1, 3) + m * m * comb(n+1, 3))  % MOD
if __name__ == "__main__":
    sol = Solution()
    print(sol)