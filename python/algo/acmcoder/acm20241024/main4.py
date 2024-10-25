from functools import cache

mod = 998244353
n, m, k = [int(i) for i in input().split()]

@cache
def dfs(prev:int, i:int):
    if i == n-1: return 1

    res = 0
    for next in range(m):
        if abs(next-prev) >= k:
            res += dfs(next, i+1)
    
    return res % 998244353


ans = 0
for i in range(m):
    ans = (ans + dfs(i, 0)) % 998244353

print(ans)