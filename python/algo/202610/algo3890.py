from bisect import bisect_right
from collections import defaultdict
from sortedcontainers import SortedSet

cubes = SortedSet()
for i in range(1, 1001):
    cubes.add(i * i * i)

cnt = defaultdict(int)
for i in range(1000):
    for j in range(i, 1000):
        val = cubes[i] + cubes[j]
        if val > 10**9: break
        cnt[val] += 1

ans = []
for k, v in cnt.items():
    if v > 1: ans.append(k)
ans.sort()

class Solution:
    def findGoodIntegers(self, n: int) -> list[int]:
        inx = bisect_right(ans, n)
        return ans[:inx]