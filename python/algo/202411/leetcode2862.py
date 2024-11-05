from collections import defaultdict
from math import isqrt
from typing import List

N = 10 ** 4
min_prime_factor = [i for i in range(N+1)] 

for i in range(2, isqrt(N)+1):
    if min_prime_factor[i] == i:
        for j in range(i*i, N+1, i):
            min_prime_factor[j] = i

# 周赛 363
class Solution:
    def maximumSum(self, nums: List[int]) -> int:
        # 自行解答 埃氏筛 并查集
        n = len(nums)
        
        subsum = [-1] + [-v for v in nums]

        def find(x:int) -> int:
            if subsum[x] < 0:
                return x
            else:
                subsum[x] = find(subsum[x])
                return subsum[x]

        def union(u, v):
            rv = find(v)
            ru = find(u)
            if rv != ru:
                subsum[ru] += subsum[rv]
                subsum[rv] = ru

        for v in range(4, n+1):
            cnt, x = defaultdict(int), v

            while min_prime_factor[x] != x:
                cnt[min_prime_factor[x]] += 1
                x //= min_prime_factor[x]
                
            cnt[min_prime_factor[x]] += 1

            y = v
            for f, c in cnt.items():
                y //= pow(f, 2 * (c // 2))
            if y != v:
                union(y, v)

        return  -min(subsum)

if __name__ == "__main__":
    sol = Solution()
    nums = [8,10,3,8,1,13,7,9,4]
    print(sol.maximumSum(nums))