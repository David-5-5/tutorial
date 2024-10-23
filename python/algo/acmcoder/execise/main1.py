from math import sqrt

def solution():
    n, m = [int(i) for i in input().split()]

    ans = 0 
    for _ in range(m):
        ans += n
        n = sqrt(n)

    # print(round(ans,2))
    print(f"{ans:.2f}")

while True:
    try:
        solution()
        # solve(data) # 核心函数
    except:
        break


