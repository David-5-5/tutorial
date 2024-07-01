from math import isqrt
from typing import List

N = 10 ** 5
# 优化 筛至平方根
min_prime_factor = [i for i in range(N + 1)] 

for i in range(2, isqrt(N)+1):
    if min_prime_factor[i] == i:
        for j in range(i*i, N+1, i):
            min_prime_factor[j] = i

class Solution:
    def largestComponentSize(self, nums: List[int]) -> int:
        n = len(nums)
        
        adt = [-1] * n
        
        primes = {}

        def find(x:int) -> int:
            if adt[x] < 0:
                return x
            else:
                adt[x] = find(adt[x])
                return adt[x]
        
        def union(x:int, y:int) -> int:
            root1 = find(x)
            root2 = find(y)
            if root1 == root2:
                return -adt[root1]
            adt[root1] += adt[root2]
            adt[root2] = root1

            return -adt[root1]

        for i, v in enumerate(nums):
            while v != 1:
                minf = min_prime_factor[v]
                if minf in primes:
                    union(primes[minf], i)
                else:
                    primes[minf] = i
                v //= minf
        return max(-adt[i] for i in range(n))

if __name__ == "__main__":
    sol = Solution()
    nums = [2,3,6,7,4,12,21,39]
    print(sol.largestComponentSize(nums))
            