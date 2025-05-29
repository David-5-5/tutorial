import numpy as np
import math


def recursive_fft(a):
    n = len(a)
    if n == 1:
        return a
    omega = np.exp(2j * np.pi / n)
    y_0 = recursive_fft(a[::2])
    y_1 = recursive_fft(a[1::2])
    y = np.zeros(n, dtype=complex)
    for k in range(n//2):
        y[k] = y_0[k] + omega**k * y_1[k]
        y[k + n//2] = y_0[k] - omega**k * y_1[k]
    return y

a = np.array([1, 2, 3, 4, 5, 6, 7, 8], dtype=complex)
print("The original vector of coefficient :\n%s \n" %(a))
y = recursive_fft(a)

print("Recursive fft result :\n%s \n" %(y))

def bit_reverse(a):
    n = len(a)
    rev = [0] * n
    bits = int(math.log2(n))
    for i in range(n):
        rev[i] = (rev[i>>1] >> 1) | (i & 1) << (bits-1)
    for i in range(n//2):
        if i < rev[i]:
            a[i], a[rev[i]] = a[rev[i]], a[i]


def iterative_fft(a):
    bit_reverse(a)
    n = len(a)
    # expo = int(math.log2(n))
    m = 1
    while m < n:
        # m = 1 << i
        omega = np.exp(1j * np.pi / m)    #
        for k in range(0, n, m*2):
            w = 1
            for j in range(m):
                t = w * a[k + j + m]
                u = a[k+j]
                a[k+j] = u + t
                a[k+j+m] = u-t
                w *= omega
        m <<= 1


def inv_fft(a):
    n = len(a)
    bit_reverse(a)
    # expo = int(math.log2(n))
    # for i in range(1, expo+1):
    #     m = 1 << i
    m = 1
    while m < n:        
        omega = np.exp(-1j * np.pi / m)    #
        for k in range(0, n, m*2):
            w = 1
            for j in range(m):
                t = w * a[k + j + m]
                u = a[k+j]
                a[k+j] = u + t
                a[k+j+m] = u-t
                w *= omega
        m <<= 1
    for i in range(n): a[i] /= n


a = np.array([1, 2, 3, 4, 5, 6, 7, 8], dtype=complex)

iterative_fft(a)
print("Iterative fft result :\n%s \n" %(a))
inv_fft(a)
print("Inverse fft which recover to original(with error) :\n%s \n" %(a))


