# O(n)
import time
from typing import List

MOD = 10 ** 9 + 7
def fib(n:int) -> int:
    f0 = f1 = 1
    if n == 0 or n == 1: return 1
    for _ in range(2, n+1):
        next = (f1 + f0) % MOD
        f0, f1 = f1, next
    return f1

begin = time.time()
print(fib(10**7))

print("Compute fib duration: ", time.time() - begin)


# 矩阵乘法
def pow(a:List[List[int]], b:List[List[int]]) -> List[List[int]]:
    r, m, c = len(a), len(a[0]), len(b[0])
    res = [[0] * c for _ in range(r)]
    for i in range(r):
        for j in range(c):
            for k in range(m):
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD
    return res

# 矩阵快速幂
def fib_matrix(n:int) -> tuple:
    trans = [[1,1], [1,0]]
    if n < 2: return trans[0][1]

    ans = [[1,0],[1,0]]
    while n:
        if n&1:
            ans = pow(ans,trans)
        trans = pow(trans,trans)
        n //= 2
    return ans[0][0]

begin = time.time()
print(fib_matrix(10 ** 8))

print("Compute fib in matrix duration: ", time.time() - begin)

# 从矩阵的快速幂推出快速倍增
# [ [Fk, Fk-1]
# [ Fk, Fk-2]]
# F2k = F
# 快速倍增法 rapid binary lifting 
def fib_lift(n:int) -> tuple:
    if n == 0: return 0, 1
    f, s = fib_lift(n >> 1)
    c = (f * (2 * s - f)) % MOD
    d = (f * f + s * s) % MOD
    if n & 1: return d, (c+d)%MOD
    else: return c,d

begin = time.time()
print(fib_lift(10**8)[1])

print("Compute fib in binary lifting duration: ", time.time() - begin)