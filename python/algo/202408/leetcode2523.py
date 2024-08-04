from bisect import bisect_left
from math import isqrt
from typing import List

n = 10**6
primes = []
is_prime = [True] * (n+1)
is_prime[0]  = is_prime[1] = False

for i in range(2, isqrt(n)+1):
    if is_prime[i]:
        for j in range(i*i, n+1, i):
            is_prime[j] = False

for i in range(2, n + 1):
    if is_prime[i]:
        primes.append(i)


class Solution:
    def closestPrimes(self, left: int, right: int) -> List[int]:
        res = [-1, -1]
        inx = bisect_left(primes, left)

        for i in range(inx, len(primes)):
            if i+1 < len(primes) and primes[i+1] <= right: # 判断 i+1是否越界
                if res[0] == -1 or primes[i+1]-primes[i] < res[1]-res[0]:
                    res = [primes[i], primes[i+1]]
            else:
                break

        return res

if __name__ == "__main__":
    sol = Solution()
    print(sol.closestPrimes(4, 6))