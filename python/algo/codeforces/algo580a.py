from typing import List
import sys

input = sys.stdin.readline()

n = int(input)
res = 0
input = sys.stdin.readline()
a = [int(x) for x in input.split(" ")]
stack = []

for i in range(n):
    if stack and stack[-1] > a[i]:
        res = max(res, len(stack))
        del stack[:]
    stack.append(a[i])

res = max(res, len(stack))

sys.stdout.write(str(res) + "\n")

