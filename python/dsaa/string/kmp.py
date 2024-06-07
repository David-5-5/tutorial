# Python program for KMP Algorithm
def KMPSearch(pat, txt):
    M = len(pat)
    N = len(txt)
 
    # create lps[] that will hold the longest prefix suffix
    # values for pattern
    lps = [0]*M
    j = 0 # index for pat[]
 
    # Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps)
 
    i = 0 # index for txt[]
    while (N - i) >= (M - j):
        if pat[j] == txt[i]:
            i += 1
            j += 1
 
        if j == M:
            print ("Found pattern at index " + str(i-j))
            j = lps[j-1]
 
        # mismatch after j matches
        elif i < N and pat[j] != txt[i]:
            # Do not match lps[0..lps[j-1]] characters,
            # they will match anyway
            if j != 0:
                j = lps[j-1]
            else:
                i += 1
 
def computeLPSArray(pat, M, lps):
    len = 0 # length of the previous longest prefix suffix
 
    lps[0] # lps[0] is always 0
    i = 1
 
    # the loop calculates lps[i] for i = 1 to M-1
    while i < M:
        if pat[i]== pat[len]:
            len += 1
            lps[i] = len
            i += 1
        else:
            # This is tricky. Consider the example.
            # AAACAAAA and i = 7. The idea is similar
            # to search step.
            if len != 0:
                len = lps[len-1]
 
                # Also, note that we do not increment i here
            else:
                lps[i] = 0
                i += 1

with open('./dsaa/string/txt.txt') as file:
    s = file.read()

with open('./dsaa/string/pattern.txt') as file:
    p = file.read() 

with open('./dsaa/string/txt2.txt') as file:
    s2 = file.read()

with open('./dsaa/string/pattern2.txt') as file:
    p2= file.read()

from datetime import datetime
begin = datetime.now()
KMPSearch(p, s)
print((datetime.now()- begin).total_seconds())

# This code is contributed by Bhavya Jain


# As following code is writed by studing algo from OI-Wiki

# Calculate prefix function with naive algo
# The time complexity is O(n**3)
def prefix_function_naive(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        for j in range(i, -1, -1):
            if s[0:j] == s[i+1-j:i+1]:
                pi[i] = j
                break

    return pi

begin = datetime.now()
# For performance, truncate 3000 charactes.
# prefix_function_naive(s[0:3000])
# print((datetime.now()- begin).total_seconds())

# Calculate prefix function with optimize：
# for pi[i], the max is pi[i-1] + 1, so iterate j from 'pi[i-1] + 1' instead of 'i'
# The time complexity is O(n**2)
def prefix_function_optimize_1(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        for j in range(pi[i-1]+1, -1, -1):
            if s[0:j] == s[i+1-j:i+1]:
                pi[i] = j
                break

    return pi

# begin = datetime.now()
# prefix_function_optimize_1(s)
# print((datetime.now()- begin).total_seconds())

# Calculate prefix function with more optimize：
# for pi[i], the max is pi[i-1] + 1, so iterate j from 'pi[i-1] + 1' instead of 'i'
# The time complexity is O(n**2)
def prefix_function(s):
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        j = pi[i-1]
        while j>0 and s[j] != s[i]:
            j = pi[j-1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
    return pi

# begin = datetime.now()
# prefix_function(s)
# print((datetime.now()- begin).total_seconds())



def kmp_prefix_function(p:str, txt:str):
    s = p + "#" + txt
    n = len(s)
    pi = [0] * n
    for i in range(1, n):
        j = pi[i-1]
        while j>0 and s[j] != s[i]:
            j = pi[j-1]
        if s[i] == s[j]:
            j += 1
        pi[i] = j
        if j == len(p):
            print ("Found pattern at index " + str(i-2*j))
    return pi

begin = datetime.now()
kmp_prefix_function(p, s)
print((datetime.now()- begin).total_seconds())
begin = datetime.now()
kmp_prefix_function(p2, s2)
print((datetime.now()- begin).total_seconds())

# # Compare the computeLPSArray and prefix_function
# def compare(pat):
#     m = len(pat)
#     lps = [0] * m
#     computeLPSArray(pat, m, lps)
#     pi = prefix_function(pat)

#     for i in range(m):
#         if lps[i] != pi[i]:
#             print(f"The array is not match at {i}, {lps[i]} != {pi[i]}")
#             return
#     print("The result of computeLPSArray and prefix_function is match")
#     print(f"The len of lps is {len(lps)}, pf is {len(pi)}")
# compare(p)
# compare(p2)



def boyer_moore(pat, txt):
    '''
    参考算法4 手写boyer-moore最基本的算法
    '''
    txtlen = len(txt)
    patlen = len(pat)
    badRight = [-1] * 256
    for i in range(patlen):
        badRight[ord(pat[i])] = i
    
    while i <= txtlen-patlen:
        for j in range(patlen-1, -1, -1):
            if (txt[i+j] != pat[j]):
                i += max(1, j-badRight[ord(txt[i+j])])
                break
            if j == 0:
                print ("Found pattern at index " + str(i))
                # 下面语句代替i += 1, 相当于先执行i += 1
                # 下一轮 执行 i += max(1, j-badRight[ord(txt[i+j])]), 减少一次比较
                # txt[i+patlen] == pat[patlen-1], badRight[ord(txt[i+patlen])] = patlen-1,
                # i 实际也 +1
                i += (patlen-badRight[ord(txt[i+patlen])] if i+patlen<txtlen else 1)


boyer_moore("NEEDLE", "FINDINATHAYSTACKNEEDLE")

begin = datetime.now()
boyer_moore(p, s)
print((datetime.now()- begin).total_seconds())
begin = datetime.now()
boyer_moore(p2, s2)
print((datetime.now()- begin).total_seconds())