from math import factorial
from typing import List

# copy from 2954
# 组合数模板 组合数 求 逆元 
# replace math.comb 
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


class Solution:
    def minMaxSums(self, nums: List[int], k: int) -> int:
        
        nums.sort()
        n, ans = len(nums), 0

        for i, v in enumerate(nums):
            cnt = sum(comb(n-i-1, j) for j in range(k) if n-i-1 >= j) % MOD
            ans += (cnt * (v+nums[n-i-1]))
        return ans % MOD

    def minMaxSums2(self, nums: List[int], k: int) -> int:
        # 优化后的组合求和的递推式
        nums.sort()
        n, ans = len(nums), 0
        # \sum_{i=0}^{k-1} c_{n+1}^i = 2 * \sum_{i=0}^{k-1} c_n^i - c_n^{k-1}
        s = 1
        for i, v in enumerate(nums):
            ans += s * (v + nums[n-i-1])
            s = (s*2 - (comb(i, k-1) if i>=k-1 else 0)) % MOD

        return ans % MOD

if __name__ == "__main__":
    sol = Solution()
    print(sol)