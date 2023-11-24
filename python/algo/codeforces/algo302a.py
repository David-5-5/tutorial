from typing import List
def count(a: List[int]) -> List[int]:
    res = 0

import sys

input = sys.stdin.readline()
n, m = [int(x) for x in input.split(" ")]

input = sys.stdin.readline()
a = [int(x) for x in input.split(" ")]

res = 0
for i in range(n):
    if a[i] == 1:
        res += 1
res = min(res, n - res)

for i in range(m):
    input = sys.stdin.readline()
    l, r =  [int(x) for x in input.split(" ")]
    result = 1 if (r-l) % 2 == 1 and (r-l+1) // 2 <= res else 0
    sys.stdout.write(str(result) + "\n")


