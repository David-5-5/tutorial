
# Python3 program for Naive Pattern
# Searching algorithm


def search(pat, txt):
    M = len(pat)
    N = len(txt)
    count = 0
    # A loop to slide pat[] one by one */
    for i in range(N - M + 1):
        j = 0
 
        # For current index i, check
        # for pattern match */
        while(j < M):
            count += 1
            if (txt[i + j] != pat[j]):
                break
            j += 1
            count += 1
 
        if (j == M):
            print("Pattern found at index ", i)

    print("count = ", count)
# Driver's Code
if __name__ == '__main__':
    # txt = "AABAACAADAABAAABAA"
    # pat = "AABA"
     
    # # Function call
    # search(pat, txt)

    with open('./python/dsaa/stringmatch/txt.txt') as file:
        s = file.read()
    
    with open('./python/dsaa/stringmatch/pattern.txt') as file:
        p = file.read()

    with open('./python/dsaa/stringmatch/txt2.txt') as file:
        s2 = file.read()
    
    with open('./python/dsaa/stringmatch/pattern2.txt') as file:
        p2= file.read()

    from datetime import datetime
    begin = datetime.now()
    search(p, s)
    print((datetime.now()- begin).total_seconds())
    begin = datetime.now()
    search(p2, s2)
    print((datetime.now()- begin).total_seconds())