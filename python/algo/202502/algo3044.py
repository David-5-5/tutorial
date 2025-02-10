from math import isqrt
from typing import Counter, List

# 周赛 385
class Solution:
    def mostFrequentPrime(self, mat: List[List[int]]) -> int:
        def is_prime(n: int) -> bool:
            return all(n % i for i in range(2, isqrt(n) + 1))

        m, n = len(mat), len(mat[0])
        cnt = Counter()

        for i in range(m):
            for j in range(n):
                for dx, dy in (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1):
                    val, x, y = mat[i][j], i + dx, j + dy # val < 10, 无需记录
                    while 0 <= x < m and 0 <=y < n:
                        val = val * 10 + mat[x][y]
                        if val in cnt or is_prime(val):
                            cnt[val] += 1
                        x += dx
                        y += dy

        ans, freq = -1, 0
        for k, v in cnt.items():
            if v > freq:
                ans = k
                freq = v
            elif v == freq: ans = max(ans, k)
        return ans