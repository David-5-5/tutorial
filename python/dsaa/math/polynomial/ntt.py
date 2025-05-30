from typing import List
import math

n = 8
q = 17

def recursive_fft(a: List[int], g: int):
    n = len(a)
    if n == 1:
        return a
    
    y_0 = recursive_fft(a[::2], pow(g, 2, q))
    y_1 = recursive_fft(a[1::2], pow(g, 2, q))
    y = [0] * n
    for k in range(n//2):
        y[k] = (y_0[k] + pow(g, k, q) * y_1[k]) % q
        y[k + n//2] = (y_0[k] - pow(g, k, q) * y_1[k]) % q
    return y

a = [i+1 for i in range(8)]
print("The original vector of coefficient :\n%s \n" %(a))
y = recursive_fft(a, 2)

print("Recursive fft result :\n%s \n" %(y))

def bit_reverse(a:List[int]):
    rev = [0] * n
    bits = int(math.log2(n))
    for i in range(n):
        rev[i] = (rev[i>>1] >> 1) | (i & 1) << (bits-1)
    for i in range(n//2):
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]


def iterative_ntt(a:List[int], g:int):
    bit_reverse(a)
    n = len(a)
    m = 1
    while m < n:
        root = pow(g, n // 2 // m, q)  # 计算m次本原单位根

        for k in range(0, n, m*2):
            w = 1
            for j in range(m):
                t = w * a[k + j + m] % q
                u = a[k+j]
                a[k+j] = (u + t) % q
                a[k+j+m] = (u-t) % q
                w = w * root % q
        m <<= 1


def inv_ntt(a:List[int], g:int):
    g_inv = pow(g, q-2, q)  # g的逆元
    iterative_ntt(a, g_inv)
    n_inv = pow(n, q-2, q)
    for i in range(n):
        a[i] = a[i] * n_inv % q


a = [i+1 for i in range(8)]

iterative_ntt(a, 2)
print("Iterative ntt result :\n%s \n" %(a))
inv_ntt(a, 2)
print("Inverse ntt which recover to original :\n%s \n" %(a))


