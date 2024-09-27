MOD = 10 ** 9 + 7

n = int(input().strip())
nums = [int(i) for i in input().split()]

f = [0] * (n + 1)
f[0] = 1
for i in range(1, n+1):
    color = [0] * 10
    for j in range(i, 0, -1):
        color[nums[j-1]] += 1
        if color[nums[j-1]] > 1:
            break
        f[i] = (f[i] + f[j-1]) % MOD

print(f[n])

