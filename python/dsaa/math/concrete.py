# concrete math

def josephus(n: int) -> int: # m = 2
    mask = (1 << n.bit_length()-1) - 1
    return ((mask & n) << 1) + 1

# page 20
n = int("101101101101011", 2)

def f(n: int, v: int) :
    for i in range(v):
        n = josephus(n)
        print(i+1, "th: ", n, " ", bin(n))

