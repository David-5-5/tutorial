import random
import bisect
a = [random.randint(1,30) for _ in range(15)]

print(a)
dp = [a[0]]
ans = 1
for i in range(1, len(a)):
    if a[i] >= dp[-1]:
        dp.append(a[i])
        ans += 1
    else:
        inx = bisect.bisect_right(dp, a[i])
        dp[inx] = a[i]

print(ans)