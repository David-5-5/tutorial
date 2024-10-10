# 字节笔试题

from itertools import accumulate

n = int(input().strip())
h = [int(i) for i in input().split()]
h.append(0) # 哨兵
presum = list(accumulate(h, initial=0))

maxArea = 0
stack = []
for i in range(len(h)): # n+1 != len(h)

    while stack and h[stack[-1]] >= h[i]:
        inx = stack.pop(-1)
        l = stack[-1] if stack else -1
        maxArea = max(maxArea, h[inx] * (presum[i]- presum[l+1]))
    stack.append(i)

print(maxArea)