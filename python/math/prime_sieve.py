from typing import List
from math import isqrt

def eratosthenes(n:int) -> List[int]:
    primes = []
    is_prime = [True] * (n+1)
    is_prime[0]  = is_prime[1] = False

    for i in range(2, n+1):
        if not is_prime[i]: continue
        primes.append(i)
        if i*i > n: continue
        # 倍数从当前素数开始, 类如2 * 2, 后续元素 + 2
        # 3 从 3 * 3 开始,  后续元素 + 3,  不需要从 6 开始
        # 同理 5, 从 5 * 5开始,  后续元素 + 5 
        for j in range(i*i, n+1, i):
            is_prime[j] = False

    return primes

def eratosthenes2(n:int) -> List[int]:
    # 优化 筛至平方根
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

    return primes

def eratosthenes2(n:int) -> List[int]:
    # 优化 筛至平方根
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

    return primes

# 使用最小质因子代替数组 min_prime_factor[] 代替 is_prime[]
# 若  min_prime_factor[i] == i, 表示 i 是素数
# 若  min_prime_factor[i] != i, 表示 i 不是质数, 是质数 p 的倍数, 则 min_prime_factor[i] 是 p
# 不断循环 min_prime_factor[min_prime_factor[i]//p], 直至 min_prime_factor[i] == i 可计算出 i 的所有质因数
def eratosthenes2_min_prime_factor(n:int) -> List[int]:
    # 优化 筛至平方根
    min_prime_factor = [i for i in range(n+1)] 

    for i in range(2, isqrt(n)+1):
        if min_prime_factor[i] == i:
            for j in range(i*i, n+1, i):
                min_prime_factor[j] = i

    return min_prime_factor

def euler(n:int):
    primes = []
    not_prime = [False] * (n+1)
    for i in range(2, n + 1):
        if not not_prime[i]:
            primes.append(i)
        for pri_j in primes:
            if i * pri_j > n:
                break
            not_prime[i * pri_j] = True
            if i % pri_j == 0:
                """
                i % pri_j == 0
                换言之, i 之前被 pri_j 筛过了
                由于 pri 里面质数是从小到大的, 所以 i 乘上其他的质数的结果一定会被
                pri_j 的倍数筛掉, 就不需要在这里先筛一次, 所以这里直接 break
                掉就好了
                """
                break
    return primes


# 数论中，欧米茄Ω, ω 分别表示 Ω(n) 是 n 的质因数的个数, 和 ω(n) 是 n 不同质因数个数
# 生成 omega(n) 生成 n及以下所有不同质因数个数
def omega(n:int) -> int:
    N = n + 1
    g = [0] * N
    for i in range(2, N):  # 预处理 omega
        if g[i] == 0:  # i 是质数
            for j in range(i, N, i):
                g[j] += 1  # i 是 j 的一个质因子

# 自行解答，寻求最优解 ...
def Omega(n:int) -> int:
    N = n + 1
    g = [-1] * N
    min_f = eratosthenes2_min_prime_factor(n)
    
    def dfs(i):
        if min_f[i] == i:
            g[i] = 1
        else:
            g[i] = dfs(i//min_f[i]) + 1
        return g[i]
    for i in range(n, 1, -1):
        if g[i] == -1:
            dfs(i)

from datetime import datetime

begin = datetime.now()
eratosthenes(10 ** 6)
print("Execute eratosthenes(10 ** 6) duration %f s",(datetime.now()- begin).total_seconds())

begin = datetime.now()
eratosthenes2(10 ** 6)
print("Execute eratosthenes2(10 ** 6) duration %f s",(datetime.now()- begin).total_seconds())

begin = datetime.now()
euler(10 ** 6)
print("Execute euler(10 ** 6) duration %f s",(datetime.now()- begin).total_seconds())


begin = datetime.now()
omega(10 ** 5)
print("Execute omega(10 ** 5) duration %f s",(datetime.now()- begin).total_seconds())

begin = datetime.now()
Omega(10 ** 5)
print("Execute Omega(10 ** 5) duration %f s",(datetime.now()- begin).total_seconds())
