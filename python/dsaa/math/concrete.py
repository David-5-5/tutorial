# concrete math

def josephus(n: int) -> int: # k = 2
    mask = (1 << n.bit_length()-1) - 1
    return ((mask & n) << 1) + 1


def j(n:int, k:int) -> int :
    if n == 1: return 0
    return (j(n-1, k) + k) % n

# page 20
n = int("101101101101011", 2)

def f(n: int, v: int) :
    for i in range(v):
        n = josephus(n)
        print(i+1, "th: ", n, " ", bin(n))

print(j(100, 5))
