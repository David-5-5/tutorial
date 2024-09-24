from functools import cache
from typing import Counter, List

PRIMES = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
NSQ_MASK = [0] * 31

for i in range(2, 31):
    for j, p in enumerate(PRIMES):
        if i % p == 0:
            if i % (p*p) == 0:
                NSQ_MASK[i] = -1
            NSQ_MASK[i] |= 1 << j

MOD = 10 ** 9 + 7
# 周赛 333
class Solution:
    def squareFreeSubsets(self, nums: List[int]) -> int:
        # 参考题解  背包
        MASK = 1 << (len(PRIMES))
        f = [0] * MASK
        f[0] = 1
        for v in nums:
            mask = NSQ_MASK[v]
            if mask >= 0:
                for j in range(MASK-1, mask-1, -1):
                    if (mask | j) == j:
                        f[j] = (f[j] + f[j-mask]) % MOD
        return (sum(f) - 1) % MOD


    def squareFreeSubsets2(self, nums: List[int]) -> int:
        # 参考题解  状压DP
        MASK = 1 << (len(PRIMES))
        f = [0] * (MASK)

        cnt = Counter(nums)
        f[0] = pow(2, cnt[1], MOD)
        for v, c in cnt.items():
            mask = NSQ_MASK[v]
            if mask > 0:
                for j in range(MASK-1, -1, -1):
                    if (mask & j) == 0:
                        f[mask | j] = (f[mask | j] + f[j] * c)% MOD
        return (sum(f) - 1) % MOD

if __name__ == "__main__":
    sol = Solution()
    nums = [3,4,4,5]
    print(sol.squareFreeSubsets2(nums))