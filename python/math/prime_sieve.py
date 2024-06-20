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
            
from datetime import datetime

print(eratosthenes(10))
print(eratosthenes(20))
print(eratosthenes(100))
print(euler(10))
print(euler(20))
print(euler(100))
begin = datetime.now()
eratosthenes(10 ** 6)
print((datetime.now()- begin).total_seconds())

begin = datetime.now()
eratosthenes2(10 ** 6)
print((datetime.now()- begin).total_seconds())

begin = datetime.now()
euler(10 ** 6)
print((datetime.now()- begin).total_seconds())

N = 10 ** 5 + 1




# 求 数 i 不同质因子的数量
g = [0] * N

for i in range(2, N):  # 预处理 omega
    if g[i] == 0:  # i 是质数
        for j in range(i, N, i):
            g[j] += 1  # i 是 j 的一个质因子
