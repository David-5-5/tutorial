from bisect import bisect_left
from itertools import accumulate


def solution():
    m, n = [int(i) for i in input().split()]

    ans = []
    for v in range(m, n+1):
        x1, x2, x3 = v // 100, (v % 100) // 10, (v % 100) % 10
        if x1 * x1 * x1 + x2 * x2 * x2 + x3 * x3* x3 == v:
            ans.append(str(v))

    presum = list(accumulate([int(v) for v in ans], initial=0))
    print(presum)
    print(bisect_left(presum, 120))

    # print(round(ans,2))
    print(" ".join(ans)) if ans else print("no")

while True:
    try:
        solution()
    except:
        break
    # except Exception as err:
    #     print(err)
    #     break


