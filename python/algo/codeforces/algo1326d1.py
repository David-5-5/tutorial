from typing import List
import sys

def manacher(s: str) -> (List[int], List[int]):
    n = len(s)
    d1 = [0] * n
    d2 = [0] * n
    l, r  = 0, -1
    for i in range(n):
        if i <= r:
            d1[i] = min(d1[l+r-i], r-i)
        while 0 <= i - d1[i] and i + d1[i] < n and s[i - d1[i]] == s[i + d1[i]]:
            d1[i] += 1
        if i + d1[i] > r:
            l, r = i - d1[i], i + d1[i]
    
    l, r  = 0, -1
    for i in range(n):
        if i <= r:
            d2[i] = min(d2[l+r-i+1], r-i)
        while 0 <= i - d2[i] - 1 and i + d2[i] < n and s[i - d2[i] - 1] == s[i + d2[i]]:
            d2[i] += 1
        if i + d2[i] > r:
            l, r = i - d2[i]-1, i + d2[i]
    return (d2, d1)

def solution(s: str):
    n = len(s)
    d = manacher(s)

    def find(s: str, l:int ,r: int) -> str:
        if l == r: return s[l]
        if l > r: return ""

        mid, rem = l + (r-l+1) // 2, (r-l+1) % 2
        if d[rem][mid] + mid == r + 1:
            return s[l:r+1]

        lmax = 1
        for i in range(l+1, mid+1):
            if i - d[0][i] <= l:
                lmax = max(lmax, (i-l)*2)
            if i + 1 - d[1][i] <= l and i<mid:
                lmax = max(lmax, (i-l+1)*2-1)

        rmax = 1
        for i in range(r, mid-1, -1):
            if i>mid and i - 1 + d[0][i] >= r:
                rmax = max(rmax, (r-i+1)*2)
            if i -1 + d[1][i] >= r:
                rmax = max(rmax, (r-i+1)*2-1)
        
        midstr = ""
        count = 0
        while s[l+count] == s[r-count]:
            count += 1
        if count > 0:
            midstr = s[l:l+count] + find(s, l+count, r-count) + s[r-count+1:r+1]
        
        maxf = max(lmax, rmax, len(midstr))
        if maxf == lmax:
            return s[l:l+lmax]
        elif maxf == rmax:
            return s[r-rmax+1:r+1]
        else:
            return midstr
    return find(s, 0, n -1)

# codeforce i/o
t = int(sys.stdin.readline())
for i in range(t):
    line = sys.stdin.readline().strip( )
    answer = solution(line)
    sys.stdout.write(solution(line) + "\n")

# print(solution("a"))
# print(solution("abcdfdcecba"))
# print(solution("abbaxyzyx"))
# print(solution("codeforces"))
# print(solution("acbba"))
# print(solution("ababaa"))

# import random
# with open('output.txt') as file:
#     for i in range(10 ** 5):
#         file.write(str(i) + "\n")
        
    